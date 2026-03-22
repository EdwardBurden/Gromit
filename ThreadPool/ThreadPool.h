#pragma once
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

class ThreadPool;

std::mutex consoleMutex;

void print(const char* string)
{
	std::lock_guard lock(consoleMutex);
	printf("Thread_%i ", std::this_thread::get_id());
	printf(string);
	printf("\n");
}

class WorkerThread
{
public:
	WorkerThread();
	WorkerThread(ThreadPool* pool, int index);

	WorkerThread(const WorkerThread&) = delete;
	WorkerThread& operator=(const WorkerThread&) = delete;

	WorkerThread(WorkerThread&&);
	WorkerThread& operator=(WorkerThread&&);
	void Run();
	void Stop();
	~WorkerThread();

private:
	ThreadPool* m_pool;
	std::thread m_thread;
	int m_index;
	//std::string m_debugOutput;
};

class ThreadPool
{
public:
	ThreadPool(size_t size);
	void Expand(size_t size);
	void Shrink(size_t size);
	void EnqueueTask(std::function<void()> task);
	~ThreadPool();
	bool HasTasks();

	//private:
	std::vector<WorkerThread> m_workers;
	std::queue<std::function<void()>> m_tasks;
	size_t m_size;
	std::mutex m_queueLock;
	std::condition_variable m_condition;
	bool m_stopFlag;
};

//////WorkerThread

WorkerThread::WorkerThread()
{
	print("Default Constructor WorkerThread");
	m_pool = nullptr;
}

WorkerThread::WorkerThread(ThreadPool* pool, int index)
{
	m_pool = pool;
	m_index = index;
	m_thread = std::thread(&WorkerThread::Run, this);
	print("Custom Constructor WorkerThread");
}

WorkerThread::WorkerThread(WorkerThread&& other)
{
	print("Move Constructor WorkerThread");
	m_thread = std::move(other.m_thread);
	m_pool = other.m_pool;
	m_index = other.m_index;
}

WorkerThread& WorkerThread::operator=(WorkerThread&& other)
{
	print("Move Operator WorkerThread");
	if (this == &other)
		return *this;

	m_thread = std::move(other.m_thread);
	m_pool = other.m_pool;
	m_index = other.m_index;
	return *this;
}


WorkerThread::~WorkerThread()
{
	print("Destructor WorkerThread");
	if (m_thread.joinable())
		m_thread.join();
}

void WorkerThread::Run()
{
	while (true)
	{
		std::function<void()> currentTask;
		{
			std::unique_lock<std::mutex> lock(m_pool->m_queueLock);
			m_pool->m_condition.wait(lock, [this]
				{
					auto condtionPassed = !m_pool->m_tasks.empty() || m_pool->m_stopFlag;
					return condtionPassed;
				});
			if (m_pool->m_stopFlag)
			{
				return;
			}

			currentTask = std::move(m_pool->m_tasks.front());
			m_pool->m_tasks.pop();
		}
		currentTask();
	}
}

void WorkerThread::Stop()
{
	if (m_thread.joinable())
		m_thread.join();
}

//////ThreadPool

ThreadPool::ThreadPool(size_t size)
{
	print("Custom Constructor ThreadPool");
	m_size = size;
	m_stopFlag = false;
	m_workers.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		m_workers.emplace_back(this, i);
	}
}

void ThreadPool::Expand(size_t size)
{
	print("Expand ThreadPool");
	m_size += size;
	m_workers.reserve(m_size);
	for (size_t i = 0; i < size; i++)
	{
		m_workers.emplace_back(this, i);
	}
}

void ThreadPool::Shrink(size_t size)
{
	print("Shrink ThreadPool");
	if (m_size - size <= 0)
	{
		throw std::invalid_argument("Error size is too small");
	}
	m_size -= size;
	m_workers.resize(m_size);
}

ThreadPool::~ThreadPool()
{
	print("Destructor ThreadPool");
	{
		std::unique_lock<std::mutex> lock(m_queueLock);
		m_stopFlag = true;
	}
	m_condition.notify_all();
	m_workers.clear();
}

bool ThreadPool::HasTasks()
{
	std::lock_guard lock(m_queueLock);
	return m_tasks.size() > 0;
}

void ThreadPool::EnqueueTask(std::function<void()> task)  //todo make it a promise return type
{
	{
		std::unique_lock<std::mutex> lock(m_queueLock);
		m_tasks.emplace(std::move(task));
	}
	m_condition.notify_one();
}