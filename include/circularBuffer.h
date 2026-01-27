#include <memory>

template <typename T>
class CircularBuffer {
public:
  CircularBuffer(size_t maxCap) : data_(make_unique<T[]>(maxCap)), maxCapacity_(maxCap), currSize_(0), head_(0), tail_(0) {}

  // push object onto queue - copy
  // if full, override oldest data
  // @return true if successful, false otherwise
  bool push(const T& obj) 
  {    
    data_[head_] = obj;
    if (head_ == tail_)
    {
      incrementPointer(tail_);
    }
    else
    {
      size_++;
    }
    incrementPointer(head_);

    return true;
  }

  // push object onto queue - move
  // if full, override oldest data
  // @return true if successful, false otherwise
  bool push(T&& obj) 
  {    
    data_[head_] = std::move(obj);
    if (head_ == tail_)
    {
      incrementPointer(tail_);
    }
    else
    {
      size_++;
    }
    incrementPointer(head_);

    return true;
  }

  // construct object in-place 
  template <typename... Args>
  bool emplace(Args&& args)
  {
    data_[head_] = T(std::forward<Args>(args)...);
    if (head_ == tail_)
    {
      incrementPointer(tail_);
    }
    else
    {
      size_++;
    }
    incrementPointer(head_);

    return true;

  }

  // pop oldest data off of queue
  std::optional pop()
  {
    if (isEmpty())
    {
      return std::nullopt;
    }

    T item = std::move(data_[tail_]);
    incrementPointer(tail_);
    size_--;

    return item;
  }

  bool isEmpty()
  {
    return currSize_ == 0;
  }

  bool isFull()
  {
    return currSize_ == maxCapacity_;
  }

private:
  unique_ptr<T[]> data_;
  size_t maxCapacity_;
  size_t currSize_;
  size_t head_; // index of next push()
  size_t tail_; // index of next pop()

  void incrementPointer(size_t& ptr)
  {
    ptr++;
    if (ptr >= maxCapacity_)
    {
      ptr = ptr % maxCapacity_;
    }
  }
};