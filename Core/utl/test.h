#pragma once

namespace utl
{
	class TestApi
	{
	public:
		TestApi(const char* name):
			test_name{ name }
		{

		}
		virtual void one_test() = 0;
		void run_test(size_t count)
		{
			for (size_t i = 0; i < count; i++)
			{
				one_test();
			}
		}
	private:
		const char* test_name;
	};
}