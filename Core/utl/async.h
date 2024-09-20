#pragma once
#include "./deque.h"
#include <condition_variable>

#define UTL_THREAD_POOL_WORK_COUNT 16

namespace utl
{
	enum class TASK_STATE
	{
		TASK_STATE_NONE,
		TASK_STATE_BEGIN,
		//TASK_STATE_START,
		//TASK_STATE_RUNING,
		//TASK_STATE_END,

		TASK_STATE_RUNING,
		TASK_STATE_DOWN
	};

	class task_base
	{
		friend class thread_main;
	public:
		task_base() :auto_free{ false } {}
		virtual ~task_base() {}
		virtual void action(const bool& par_life) {}//void action(const bool& par_life) override
		TASK_STATE state{};
		inline void setAutoFree(bool af) { auto_free = af; }
	protected:
		bool auto_free;
	};

	struct task_pool_private;

	// template<typename T,typename ... Args>
	// inline T* make_task(Args&&...args)
	// {
	// 	return make_pointer<T>(std::forward<Args>(args)...);
	// }

	/*inline void free_task(task_base* tb)
	{
		free_pointer<task_base>(tb);
	}*/

	class task_pool
	{
		friend class thread_main;
	public:
		task_pool();
		~task_pool();
		static task_pool& taskInstance();
		static task_pool& serverInstance();
		void wait_for_down(uint32_t timerout);//ms
		void start(task_base* task);

	private:
		task_pool_private* d;
		utl::queue<task_base*> task_queue;
		bool life;
		uint32_t thread_count;
		std::mutex task_lock;
		std::condition_variable task_cv;
	private:
		void wait_task();
		void task_active();
	};

}