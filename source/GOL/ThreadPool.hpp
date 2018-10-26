#pragma once

#include <memory>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>

class ThreadPool
{
    private:
        std::vector<std::thread> m_Threads;
        std::queue<std::function<void()>> m_Jobs;
        std::condition_variable m_CvTask, m_CvFinished;
        std::mutex m_QueueMutex;
        bool m_Running;
        int m_TotalJobs, m_TotalProcessedJobs;
    public:
        ThreadPool(int totalThreads = std::thread::hardware_concurrency());
        ~ThreadPool();
        void AddJob(std::function<void()> job);
        void WaitUntilFinished();
    private:
        void Start();
};