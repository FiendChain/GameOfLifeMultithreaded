#include "ThreadPool.hpp"
#include <iostream>

ThreadPool::ThreadPool(int totalThreads)
    : m_Running(true),
      m_TotalJobs(0),
      m_TotalProcessedJobs(0)
{
    if (totalThreads <= 0)
        throw std::runtime_error("Threadpool must have more tha 0 threads");
    else if (totalThreads > std::thread::hardware_concurrency())
        std::cout << "[Warning]: Threadpool has exceeded more than maximum core count, " << totalThreads << std::endl;

    for (unsigned int i = 0; i < totalThreads; i++)
    {
        m_Threads.emplace_back(std::bind(&ThreadPool::Start, this));
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> latch(m_QueueMutex);
        m_Running = false;
        m_CvTask.notify_all();
    }

    for (auto& thread: m_Threads)
        thread.join();
}

void ThreadPool::AddJob(std::function<void()> job)
{
    {
        std::unique_lock<std::mutex> latch(m_QueueMutex);
        m_Jobs.push(job);
    }
    m_CvTask.notify_one();
}

void ThreadPool::Start()
{
    while (true)
    {
        std::unique_lock<std::mutex> latch(m_QueueMutex);
        // wait until it needs to do task
        // or if it has stopped running and thread needs to close
        m_CvTask.wait(latch, [this] {
            return !m_Running || !m_Jobs.empty();
        });
        if (!m_Jobs.empty())
        {
            m_TotalJobs++;
            auto job = m_Jobs.front();
            m_Jobs.pop();
            latch.unlock();
            // perform asynchronously
            job();
            latch.lock();
            m_TotalProcessedJobs++;
            m_TotalJobs--;
            m_CvFinished.notify_one(); 
        }
        else if (!m_Running) // exit thread
        {
            return;
        }
    }
}

void ThreadPool::WaitUntilFinished()
{
    std::unique_lock<std::mutex> latch(m_QueueMutex);
    m_CvFinished.wait(latch, [this]() {
        return m_Jobs.empty() && m_TotalJobs == 0;
    });
}