#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <functional>
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace detail {
struct ThreadPoolJob final {
    ThreadPoolJob();
    std::mutex m_jobMutex;
    std::condition_variable m_jobCv;
    std::atomic<bool> m_jobInProgress;
    std::function<void()> m_jobFunction;
};
} // namespace

class ThreadPool final {
    public:
        ThreadPool(size_t);
        ~ThreadPool();
        template<typename Func>
        void addJob(Func &&f);
    private:
        const size_t m_numberOfThreads;
        std::vector<std::thread> m_vThread;
        std::vector<detail::ThreadPoolJob> m_vJobs;
        std::atomic<bool> m_stopFlag;
        std::atomic<unsigned int> m_threadCounter;

        void threadBody(size_t threadIndex);
};

template<typename Func>
void ThreadPool::addJob(Func &&f) {
    const size_t threadIndex = m_threadCounter.fetch_add(1) % m_numberOfThreads;
    auto & job = m_vJobs.at(threadIndex);
    // wait if job in progress
    std::unique_lock<std::mutex> lock(job.m_jobMutex);
    job.m_jobCv.wait(lock, [&job]{return !job.m_jobInProgress.load();});
    job.m_jobFunction = std::forward<std::function<void()>>(f);
    job.m_jobInProgress = true;
    job.m_jobCv.notify_all(); // notify to start job
}

#endif
