#include "cbuffermanager.h"

cBuffer::cBuffer(size_t buffer_size, cBufferManager * parent)
    :
      m_buffer(buffer_size),
      m_is_reserved(false),
      m_parent(parent)
{}

void cBuffer::reserve() noexcept {
    m_is_reserved = true;
}

void cBuffer::release() noexcept {
    m_is_reserved = false;
}

bool cBuffer::is_reserved() const noexcept {
    return m_is_reserved;
}

unsigned char *cBuffer::get_data_ptr() {
    return &m_buffer.front();
}

size_t cBuffer::get_max_size() const noexcept {
    return m_buffer.size();
}

cBufferManager::cBufferManager(size_t number_of_buffers, size_t buffer_size)
    :
      m_buffers(number_of_buffers)
{
    for (auto & buffer : m_buffers)
        buffer = std::make_unique<cBuffer>(buffer_size, this);
}

cBuffer &cBufferManager::get_free_buffer_or_wait() {
 // TODO
}
