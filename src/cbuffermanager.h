#ifndef CBUFFERMANAGER_H
#define CBUFFERMANAGER_H

#include <atomic>
//#include <condition_variable>
#include <cstddef>
#include <memory>
#include <vector>

class cBufferManager;

class cBuffer {
    public:
        cBuffer(size_t buffer_size, cBufferManager * parent);
        void reserve() noexcept;
        void release() noexcept;
        bool is_reserved() const noexcept;
        unsigned char * get_data_ptr();
        size_t get_max_size() const noexcept;
    private:
        std::vector<unsigned char> m_buffer;
        std::atomic<bool> m_is_reserved;
        cBufferManager * m_parent;
};

class cBufferManager {
    public:
        cBufferManager(size_t number_of_buffers, size_t buffer_size);
        cBuffer & get_free_buffer_or_wait();
    private:
        std::vector<std::unique_ptr<cBuffer>> m_buffers;

};

#endif // CBUFFERMANAGER_H
