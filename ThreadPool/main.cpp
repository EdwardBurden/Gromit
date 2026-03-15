//general
#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>


//concurrency
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <future>

//GOAL:
// Create a testing suite of different "tasks" that could be made randomly pushed onto a thread pool,
// the pool should queue up the tasks and then process them in a way were old threads are reused till the queue of work is done.
// A visual of what is happening should show pools active, updated per frame on  aseperate thread. 
// Each thread hsould display its id, work progress, if its waiting for resources to unlock etc.

std::mutex consoleMutex;

void print(const char* string)
{
	std::lock_guard lock(consoleMutex);
	printf("Thread_%i ", std::this_thread::get_id());
	printf(string);
	printf("\n");
}

void f1(int n)
{
	//print("executing f1");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//print("exiting f1");
}

class ThreadPool
{
public:
	ThreadPool(size_t size)
	{
		m_size = size;
		m_stopFlag = false;
		for (size_t i = 0; i < size; i++)
		{
			auto lambda = [this, i]()
				{
					while (true)
					{
						std::function<void()> currentTask;
						{
							std::unique_lock<std::mutex> lock(m_queueLock);
							m_condition.wait(lock, [this]
								{
									auto condtionPassed = !m_tasks.empty() || m_stopFlag;
									return condtionPassed;
								});
							if (m_stopFlag)
							{
								return;
							}

							currentTask = std::move(m_tasks.front());
							m_tasks.pop();
						}
						currentTask();
					}
				};

			m_threads.emplace_back(lambda);
		}
	}

	/*void Debug_PrintStatus()
	{
		std::lock_guard lock(m_queueLock);

		{
			std::lock_guard lock(consoleMutex);
			std::string output = "Threads";
			for (size_t i = 0; i < m_size; i++)
			{
				output += std::format("{}", );
			}
			"Threads [2364][123][6767][20944], 
		    "Busy[true][false][false][true], "
		    "Time[true][false][false][true], "

		}


	}*/

	~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_queueLock);
			m_stopFlag = true;
		}

		m_condition.notify_all();

		for (std::thread& w : m_threads)
		{
			if (w.joinable())
				w.join();
		}
	}

	bool HasTasks()
	{
		std::lock_guard lock(m_queueLock);
		return m_tasks.size() > 0;
	}

	/*
		template <class _Fn, class... _Args>
		void EnqueueTask(_Fn&& _Fx, _Args&&... _Ax)  //todo make it a promise return type
		{
			std::unique_lock<std::mutex> lock(m_queueLock);
			m_tasks.emplace(std::move())
	}
	*/

	void EnqueueTask(std::function<void()> task)  //todo make it a promise return type
	{
		{
			std::unique_lock<std::mutex> lock(m_queueLock);
			m_tasks.emplace(std::move(task));
		}
		m_condition.notify_one();
	}


	/*template<class F, class... Args>
		auto EnqueueTask(F&& f, Args&&... args)
		-> std::future<std::invoke_result_t<F, Args...>>
	{
		using ReturnType = std::invoke_result_t<F, Args...>;

		auto task = std::make_shared<std::packaged_task<ReturnType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

		std::future<ReturnType> future = task->get_future();

		//{
		//	std::lock_guard<std::mutex> lock(m_mutex);
		//	m_tasks.emplace([task]()
		//		{
		//			(*task)();
		//		});
		//}

		//m_condition.notify_one();

		return future;
	}*/

private:
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
	size_t m_size;
	std::mutex m_queueLock;
	std::condition_variable m_condition;
	bool m_stopFlag;
};

class  ExampleClass
{
public:
	ExampleClass();
	~ExampleClass();

	inline int Floor(double d)
	{
		//print("executing floor");
		std::this_thread::sleep_for(std::chrono::seconds((long)d));
		//print("exiting floor");
		return  (int)d;
	}
private:

};

ExampleClass::ExampleClass()
{
}

ExampleClass::~ExampleClass()
{
}


int main()
{
	ExampleClass c;
	ThreadPool pool(4);
	std::future<int> results[10];

	//auto future =

	for (size_t i = 0; i < 10; i++)
	{
		pool.EnqueueTask([] {f1(55); });
	}
	for (size_t i = 0; i < 100; i++)
	{
		//results[i] = 
		pool.EnqueueTask([&c, i] {	return c.Floor(i);	});
	}


	while (pool.HasTasks())
	{

	}


	/*std::mutex m;
	std::vector<std::jthread> pool;
	for (size_t i = 0; i < 10; i++)
	{
		pool.emplace_back(f1, std::ref(m), i);
	}*/
	// Blank

	return 0;
}
