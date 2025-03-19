#ifndef SHAREDPTR_H
#define SHAREDPTR_H

namespace DSA
{

template <typename T>
class SharedPtr
{
public:
  // Constructors
  SharedPtr(const T& data) : data_(new T(data)), count_(new size_t(1)) { }
  SharedPtr(T* data) : data_(data), count_(new size_t(1)) { }
  
  SharedPtr(const SharedPtr& other) // Copy Constructor
  {
    data_ = other.data_;
    count_ = other.count_;
    (*count_)++;
  }
  
  SharedPtr(SharedPtr&& other) noexcept : data_(other.data_), count_(other.count_) // Move Constructor
  {
    other.data_ = nullptr;
    other.count_ = nullptr;
  }

  ~SharedPtr() // Destructor
  {
    release();
  }

  // Operators
  SharedPtr& operator=(const SharedPtr& other) // copy assignment
  {
    if (this != &other)
    {
      release();

      data_ = other.data_;
      count_ = other.count_;
      (*count_)++;
    }
    return *this;
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept // move assignment
  {
    if (this != &other)
    {
      release();

      data_ = other.data_;
      count_ = other.count_;
      
      other.data_ = nullptr;
      other.count_ = nullptr;
    }
    return *this;
  }
  T& operator*() const
  {
    return *data_;
  }
  T* operator->() const
  {
    return data_;
  }
  operator bool() const
  {
    return data_ != nullptr;
  }

  // Modifiers
  void reset()
  {
    release();
    count_ = nullptr;
    data_ = nullptr;
  }

  // Getters
  size_t useCount() { return (count_) ? *count_ : 0; }

private:
  size_t* count_;
  T* data_;

  void release()
  {
    if (count_)
    {
      (*count_)--;
      if (data_ && (*count_) == 0)
      {
        delete count_;
        delete data_;
      }
    }
  }
};

// make_shared equivalent
template <typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) 
{
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace DSA

#endif  // UNORDEREDMAP_H