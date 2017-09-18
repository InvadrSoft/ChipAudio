//
// Created by Myles Inglis on 27/07/2017.
//

#ifndef CHIPAUDIO_MOVEABLEATOMIC_HPP
#define CHIPAUDIO_MOVEABLEATOMIC_HPP

#include <atomic>

namespace chip
{
    template <typename T>
    class MoveableAtomic
    {
    public:
        MoveableAtomic() {}
        MoveableAtomic(T value) : atomic_(value) {}
        MoveableAtomic(const MoveableAtomic& other) : atomic_(other.atomic_.load() ) {}
        MoveableAtomic(const MoveableAtomic&& other) : atomic_(other.atomic_.load() ) {}

        const std::atomic<T>& atomic() const { return atomic_; }

        operator T() const { return atomic_; }

        MoveableAtomic& operator=(const MoveableAtomic&& other) { atomic_ = other.atomic_.load(); return *this; }
        MoveableAtomic& operator=(const MoveableAtomic& other) { atomic_ = other.atomic_.load(); return *this; }
        MoveableAtomic& operator=(const T& value) { atomic_ = value; return *this; }

    private:
        std::atomic<T> atomic_;
    };
}

#endif //CHIPAUDIO_MOVEABLEATOMIC_HPP
