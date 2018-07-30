#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <functional>
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

// TODO: move to file
namespace detail {
    class ThreadPoolJob final {
    public:
    private:
        std::condition_variable m_cv;
        std::mutex m_mJob;
        std::atomic<bool> m_stopFlag;
    };
};

class ThreadPool final {
public:
    ThreadPool(size_t);
    template<typename Func> 
        void addJob(Func &&f);
private:
    std::vector<std::thread> m_vThread;
    std::vector<std::function<void()>> m_vJobs;
    std::atomic<bool> m_stopFlag;

    void threadBody();
};

#endif
