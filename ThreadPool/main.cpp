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

//
#include "ThreadPool.h"


//GOAL:
// Create a testing suite of different "tasks" that could be made randomly pushed onto a thread pool,
// the pool should queue up the tasks and then process them in a way were old threads are reused till the queue of work is done.
// A visual of what is happening should show pools active, updated per frame on  aseperate thread. 
// Each thread hsould display its id, work progress, if its waiting for resources to unlock etc.

void f1(int n)
{
	print("executing f1");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	print("exiting f1");
}

class  ExampleClass
{
public:
	ExampleClass();
	~ExampleClass();

	inline int Floor(double d)
	{
		print("executing floor");
		std::this_thread::sleep_for(std::chrono::seconds((long)d));
		print("exiting floor");
		return  (int)d;
	}

	inline int Special(double d)
	{
		print("executing Special");
		std::this_thread::sleep_for(std::chrono::seconds(2));
		print("exiting Special");
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
	ThreadPool pool(10);
	std::future<int> results[10];
	std::future<int> future = pool.EnqueueTaskPromise(&ExampleClass::Special, &c, 5);

	for (size_t i = 0; i < 5; i++)
	{
		auto future = pool.EnqueueTaskPromise([] {f1(55); });
		future.get();
	}
	for (size_t i = 0; i < 10; i++)
	{
		auto future = pool.EnqueueTaskPromise([&c, i] {	return c.Floor(i);	});
	}


	pool.Expand(7);
	pool.Shrink(9);
	pool.Expand(3);
	while (pool.HasTasks() || pool.AreAnyThreadActive())
	{

	}
	auto waiting = future.get();
	std::cout << waiting;
	return 0;
}
