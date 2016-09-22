//
// Created by Myles Inglis on 22/09/2016.
//

#ifndef CHIPAUDIO_SPSCRINGBUFFER_HPP
#define CHIPAUDIO_SPSCRINGBUFFER_HPP

#include <atomic>
#include <thread>
#include <array>

namespace chip
{
    /**
     * Single producer, single consumer thread-safe ring buffer template class.
     * @tparam T The type of elements contained in the buffer
     * @tparam Size Capacity of the buffer
     */
    template <typename T, int Size>
    class SPSCRingBuffer
    {
    public:
        /**
         * Default constructor.
         */
        SPSCRingBuffer()
            : begin(0), end(0)
        {}

        /**
         * Attempting to move will just reset the buffer.
         */
        SPSCRingBuffer(SPSCRingBuffer&& pattern)
            : SPSCRingBuffer()
        {}

        /**
         * Push back an element into the buffer. Thread-safe for single producer, single
         * consumer usage.
         * @param element Element to push into buffer
         * @return False if buffer was full, true if element was pushed successfully
         */
        bool push_back(const T& element)
        {
            size_t currentEnd = end;
            size_t newEnd = (currentEnd + 1) % Size;
            if(newEnd != begin)
            {
                buffer[end] = element;
                end = newEnd;
                return true;
            }
            return false;
        }

        /**
         * Pop element from front of buffer. Thread-safe for single producer, single consumer usage.
         * @param element Where to put the popped element
         * @return False if buffer was empty, true if element was successfully popped
         */
        bool pop_front(T& element)
        {
            size_t currentBegin = begin;
            if(currentBegin == end)
            {
                return false;
            }
            element = buffer[begin];
            size_t newBegin = (currentBegin + 1) % Size;
            begin = newBegin;
            return true;
        }

    private:
        std::array<T, Size + 1> buffer;
        std::atomic<size_t> begin;
        std::atomic<size_t> end;
    };
}

#endif //CHIPAUDIO_SPSCRINGBUFFER_HPP
