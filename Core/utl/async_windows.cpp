#include "./async.h"
#include "./memory.h"
#include <thread>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <array>

namespace utl
{
	
	struct task_pool_private
	{
		struct
		{
			HANDLE thread_handle;
			DWORD thread_id;
		}ctx[UTL_THREAD_POOL_WORK_COUNT];
	};

	inline uint32_t cal_thread_count()
	{
		const auto max_cpu_core = std::thread::hardware_concurrency();
		return max_cpu_core > UTL_THREAD_POOL_WORK_COUNT ? UTL_THREAD_POOL_WORK_COUNT : max_cpu_core;
	}

	class thread_main
	{
	public:
		static DWORD thread_main_func(LPVOID param)
		{
			task_pool* tp = (task_pool*)param;
			while (tp->life)
			{
				if (tp->task_queue.empty())
				{
					tp->wait_task();
				}

				task_base* runable{};
				if (false == tp->task_queue.empty() && tp->life)
				{
					std::lock_guard<std::mutex> lg{ tp->task_lock };
					if (false == tp->task_queue.empty())
					{
						runable = tp->task_queue.front();
						tp->task_queue.pop();
					}
				}

				if (runable != nullptr)
				{
					runable->action(tp->life);
					if (runable->auto_free)
					{
						free_pointer(runable);
					}
				}
			}

			return 0;
		}
	private:

	};

	task_pool::task_pool():
		d{ make_pointer<task_pool_private>() },
		task_queue{},
		life{true},
		thread_count{ cal_thread_count() },
		task_lock{},
		task_cv{}
	{
		for (uint32_t i = 0; i < thread_count; i++)
		{
			d->ctx[i].thread_handle = CreateThread(nullptr, 0, thread_main::thread_main_func, this, 0, &d->ctx[i].thread_id);
		}
	}

	task_pool::~task_pool()
	{
		this->life = false;
		task_active();
		wait_for_down(0xFFFFFFFF);
		for (uint32_t i = 0; i < this->thread_count; i++)
		{
			CloseHandle(d->ctx[i].thread_handle);
		}
		free_pointer(d);
	}

	task_pool& task_pool::taskInstance()
	{
		static task_pool ins{};
		return ins;
	}

	task_pool& task_pool::serverInstance()
	{
		static task_pool ins{};
		return ins;
	}

	void task_pool::wait_task()
	{
		std::unique_lock<std::mutex> ul{ task_lock };
		task_cv.wait(ul);
	}

	void task_pool::task_active()
	{
		task_cv.notify_all();
	}

	void task_pool::wait_for_down(uint32_t timerout)
	{
		std::array<HANDLE, UTL_THREAD_POOL_WORK_COUNT> waitables;
		for (uint32_t i = 0; i < this->thread_count; i++)
		{
			waitables[i] = d->ctx[i].thread_handle;
		}

		WaitForMultipleObjects(this->thread_count, waitables.data(), TRUE, timerout);
	}

	void task_pool::start(task_base* task)
	{
		{
			std::lock_guard<std::mutex> lg{ this->task_lock };
			this->task_queue.push(task);
		}
		task_active();
	}
}