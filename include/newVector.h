#ifndef newVECTOR_H
#define newVECTOR_H

#include <string>

namespace DSA
{

template <typename T>
class Vector 
{
public:
  /////////////////
  // Contructors //
  /////////////////
  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  ~Vector() 
  {
    delete[] data_;
  }

  // copy constructor
  Vector(Vector& other)
  {
    data_ = new T[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;

    for (size_t i = 0; i < size_; i++)
    {
      data_[i] = other.data_[i];
    }
  }

  // move constructor
  Vector(Vector&& other) noexcept
  {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ///////////////
  // Operators //
  ///////////////
  T& operator[](size_t index) { return data_[index]; }

  const T& operator[](size_t index) const { return data_[index]; }

  // copy operator
  Vector& operator=(const Vector& other)
  {
    if (this != &other)
    {
      delete[] data_;

      data_ = new T[other.capacity_];
      size_ = other.size_;
      capacity_ = other.capacity_;
  
      for (size_t i = 0; i < size_; i++)
      {
        data_[i] = other.data_[i];
      }
    }

    return *this;
  }

  // move assignment operator
  Vector& operator=(Vector&& other) noexcept
  {
    if (this != &other)
    {
      delete[] data_;
      
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    return *this;
  }

  ///////////////
  // Modifiers //
  ///////////////
  void push_back(const T& newData)
  {
    if (size_ >= capacity_)
    {
      size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
      resize(newCap);
    }

    data_[size_++] = newData;
  }

  void push_back(T&& newData)
  {
    if (size_ >= capacity_)
    {
      size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
      resize(newCap);
    }

    data_[size_++] = std::move(newData);
  }

  template<typename... Args>
  T& emplace_back(Args&&... args)
  {
    if (size_ >= capacity_)
    {
      size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
      resize(newCap);
    }

    // construct object in place
    new(&data_[size_]) T(std::forward<Args>(args)...);
    return data_[size_++];
  }

  void pop_back()
  {
    if (size_ > 0)
    {
      size_--;

      // TODO: ideally want to delete the object just popped off
    }
  }

  void clear()
  {
    // TODO: ideally want to delete all objects

    size_ = 0;
  }

  /////////////
  // Getters //
  /////////////
  size_t size() { return size_; }
  bool isEmpty() { return size_ == 0; }


private:
  T* data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t newCap)
  {
    T* newData = new T[newCap];

    for (size_t i = 0; i < size_; i++)
    {
      newData[i] = std::move(data_[i]);
    }

    delete[] data_;

    data_ = newData;
    capacity_ = newCap;
  }
};

}

#endif  // newVECTOR_H