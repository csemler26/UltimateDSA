#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include <atomic>
#include <array>

namespace DSA 
{

template <typename T, size_t Capacity>
class LockFreeQueue {
public:
  LockFreeQueue() : head_(0), tail_(0) {}

  bool enqueue(T item) 
  {
    size_t head = head_.load(std::memory_order_acquire);
    size_t nextHead = (head + 1) % Capacity; // circular buffer

    if (nextHead == tail_.load(std::memory_order_acquire)) 
    {
      return false; // Queue is full
    }

    buffer_[head].store(item, std::memory_order_release); // Atomic store
    head_.store(nextHead, std::memory_order_release);

    return true;
  }

  bool dequeue(T& item) 
  {
    size_t tail = tail_.load(std::memory_order_acquire);

    if (tail == head_.load(std::memory_order_acquire)) 
    {
      return false; // Queue is empty
    }

    item = buffer_[tail].load(std::memory_order_acquire); // Atomic load
    tail_.store((tail + 1) % Capacity, std::memory_order_release);

    return true;
  }

  size_t size()
  {
    size_t head = head_.load(std::memory_order_acquire);
    size_t tail = tail_.load(std::memory_order_acquire);

    return (head + Capacity - tail) % Capacity;
  }

private:
  std::atomic<size_t> head_;
  std::atomic<size_t> tail_;
  std::array<std::atomic<T>, Capacity> buffer_; // circular buffer of type T
};

} // namespace DSA

#endif // LOCKFREEQUEUE_H