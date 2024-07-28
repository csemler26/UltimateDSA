#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace DSA {

template <typename dataType>
class Vector {
public:
  // Constructors
  Vector();
  Vector(int size, const dataType& value);
  ~Vector();
  
  // Operator Overloads
  Vector<dataType>& operator=(const Vector<dataType>& other);
  dataType& operator[](size_t index);
  const dataType& operator[](size_t index) const;

  // Modifiers
  void clear();
  bool push_back(const dataType& val);
  bool pop_back();
  bool insert(const size_t& pos, const dataType& val);
  bool erase(const dataType& val);
  
  // Accessors
  dataType* find(const size_t& index);
  
  // General
  std::string toString() const;
  bool isEmpty() const;
  size_t size() const;
  size_t capacity() const;

private:
  size_t size_;       // number of elements
  size_t capacity_;   // number of available slots
  dataType* data_;

  void resize(size_t newCapacity);
};

template<typename dataType>
Vector<dataType>::Vector() : size_(0), capacity_(1), data_(new dataType[1])
{
}

template <typename dataType>
Vector<dataType>::Vector(int size, const dataType& value) : 
  size_(size), 
  capacity_(size), 
  data_(new dataType[size]) 
{
  std::fill(data_, data_ + size, value);
}

template<typename dataType>
Vector<dataType>::~Vector() 
{
  delete[] data_;
}

template <typename dataType>
Vector<dataType>& Vector<dataType>::operator=(const Vector<dataType>& other) 
{
  if (this != &other) 
  {
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new dataType[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
  }
  return *this;
}

template <typename dataType>
dataType& Vector<dataType>::operator[](size_t index) 
{
  return data_[index];
}

template <typename dataType>
const dataType& Vector<dataType>::operator[](size_t index) const 
{
  if (index >= size_) {
    resize(index + 1);
  }
  return data_[index];
}

template<typename dataType>
bool Vector<dataType>::push_back(const dataType& val) 
{
  if (size_ == capacity_) 
  {
    resize(capacity_ + 5);
  }
  data_[size_++] = val;
  return true;
}

template<typename dataType>
bool Vector<dataType>::insert(const size_t& pos, const dataType& val) 
{
  if (pos > size_)
  {
    return false;
  }
  
  if (size_ == capacity_) 
  {
    resize(capacity_ + 5);
  }
  
  std::move_backward(data_ + pos, data_ + size_, data_ + size_ + 1);
  data_[pos] = val;
  ++size_;
  return true;
}

template<typename dataType>
bool Vector<dataType>::pop_back() 
{
  if (size_ == 0) 
  {
    return false;
  }
  --size_;
  return true;
}

template<typename dataType>
bool Vector<dataType>::erase(const dataType& val) 
{
  auto it = std::find(data_, data_ + size_, val);
  if (it != data_ + size_) 
  {
    std::move(it + 1, data_ + size_, it);
    --size_;
    return true;
  }
  return false;
}

template <typename dataType>
dataType* Vector<dataType>::find(const size_t& index) 
{
  return (index < size_) ? &data_[index] : nullptr;
}

template<typename dataType>
std::string Vector<dataType>::toString() const
{
  std::ostringstream oss;
  oss << "[";
  for (size_t i = 0; i < size_; ++i) 
  {
    oss << data_[i];
    if ( i < size_ - 1 ) 
    {
      oss << ", ";
    }
  }
  oss << "]";

  return oss.str();
}

template<typename dataType>
bool Vector<dataType>::isEmpty() const
{
  return size_ == 0;
}

template<typename dataType>
size_t Vector<dataType>::size() const
{
  return size_;
}

template<typename dataType>
size_t Vector<dataType>::capacity() const
{
  return capacity_;
}

template<typename dataType>
void Vector<dataType>::clear() 
{
  size_ = 0;
}

template<typename dataType>
void Vector<dataType>::resize(size_t newCapacity) 
{
  if (newCapacity > capacity_) 
  {
    dataType* newData = new dataType[newCapacity];
    
    for (size_t i = 0; i < size_; ++i) 
    {
      newData[i] = std::move(data_[i]);
    }
    
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
  
  for (size_t i = size_; i < newCapacity; ++i) 
  {
    data_[i] = dataType();
  }
}

} // namespace DSA

#endif // VECTOR_H