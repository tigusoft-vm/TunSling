#include "thread_pool.h"

detail::ThreadPoolJob::ThreadPoolJob()
:
    m_jobMutex(),
    m_jobCv(),
    m_jobInProgress(false),
    m_jobFunction()
{
}

ThreadPool::ThreadPool(size_t numThreads) 
:
    m_numberOfThreads(numThreads),
    m_vThread(numThreads),
    m_vJobs(numThreads),
    m_stopFlag(false),
    m_threadCounter(0)
{
    for (size_t i = 0; i < m_vThread.size(); i++) {
        m_vThread.at(i) = std::thread([this, i] {
            threadBody(i);
        });
    }
}

ThreadPool::~ThreadPool() {
    m_stopFlag = true;
    for(auto &thread : m_vThread) {
        if(thread.joinable())
            thread.join();
    }
}

void ThreadPool::threadBody(size_t threadIndex) {
    auto & job = m_vJobs.at(threadIndex);
    while(!m_stopFlag) {
         // wait for start job
        std::unique_lock<std::mutex> lock(job.m_jobMutex);
        job.m_jobCv.wait(lock, [&job]{return job.m_jobInProgress.load();});
        job.m_jobFunction(); // <== doing job
        job.m_jobInProgress = false;
        job.m_jobCv.notify_all();
    }
}

