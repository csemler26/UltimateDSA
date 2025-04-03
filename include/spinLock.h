#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>

namespace DSA
{

class SpinLock
{
public:
  SpinLock() : flag_(ATOMIC_FLAG_INIT) {}

  void lock() 
  {
    while (flag_.test_and_set(std::memory_order_acquire)) { /* do nothing */ }
  }

  void unlock()
  {
    flag_.clear(std::memory_order_release);
  }

private:
  std::atomic_flag flag_;
};

}  // namespace DSA

#endif  // SHAREDPTR_H