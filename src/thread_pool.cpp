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
}

ThreadPool::~ThreadPool() {
    m_stopFlag = true;
    for(auto &thread : m_vThread) {
        if(thread.joinable())
            thread.join();
    }
}

void ThreadPool::threadBody(size_t threadIndex) {
    while(!m_stopFlag) {
        
        
    }
}

