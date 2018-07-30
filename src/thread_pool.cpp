#include "thread_pool.h"

ThreadPool::ThreadPool(size_t numThreads) 
: m_vThread(numThreads), m_vJobs(numThreads), m_stopFlag(false) {
    
};

ThreadPool::~ThreadPool() {
    m_stopFlag = true;
    for(auto &thread : m_vThread) {
        if(thread.joinable())
            thread.join();
    }
};

void ThreadPool::ThreadBody() {
    while(!m_stopFlag) {
        
        
    }
};
