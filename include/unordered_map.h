#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <string>
#include <sstream>

namespace DSA {

const size_t NUMBER_OF_INDEX = 10;

template <typename Key, typename Value>
class UnorderedMap {
public:
  using iterator = typename std::list<std::pair<Key, Value>>::iterator;
  using const_iterator = typename std::list<std::pair<Key, Value>>::const_iterator;

  UnorderedMap();
  ~UnorderedMap();
  bool insert(const Key& k, const Value& v);
  bool erase(const Key& k);
  
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  Value* find(const Key& k);
  Value& operator[](const Key& k);
  
  std::string toString();

  bool isEmpty();
  size_t size();
  void clear();

private:
  size_t hashFunction(const Key& k);

  std::vector<std::list<std::pair<Key, Value>>> data_;
  size_t size_;
};

template<typename Key, typename Value>
UnorderedMap<Key, Value>::UnorderedMap() : data_(NUMBER_OF_INDEX, std::list<std::pair<Key, Value>>()), size_(0) 
{
}

template<typename Key, typename Value>
UnorderedMap<Key, Value>::~UnorderedMap() 
{
}

template<typename Key, typename Value>
bool UnorderedMap<Key, Value>::insert(const Key& k, const Value& v) 
{
  size_t index = hashFunction(k);

  for (const auto& pair : data_[index])
  {
    if (pair.first == k)
    {
      return false;
    }
  }

  size_++;
  data_[index].push_back(std::make_pair(k, v));
  return true;
}

template<typename Key, typename Value>
bool UnorderedMap<Key, Value>::erase(const Key& k) 
{
  size_t index = hashFunction(k);

  for (auto it = data_[index].begin(); it != data_[index].end(); it++)
  {
    if (it->first == k)
    {
      data_[index].erase(it);
      size_--;
      return true;
    }
  }
  return false;
}

template<typename Key, typename Value>
typename UnorderedMap<Key, Value>::iterator UnorderedMap<Key, Value>::begin() 
{
  for (auto& bucket : data_) {
    if (!bucket.empty()) {
      return bucket.begin();
    }
  }
  return data_.back().end();
}

template<typename Key, typename Value>
typename UnorderedMap<Key, Value>::iterator UnorderedMap<Key, Value>::end() 
{
  return data_.back().end();
}

template<typename Key, typename Value>
typename UnorderedMap<Key, Value>::const_iterator UnorderedMap<Key, Value>::begin() const 
{
  for (const auto& bucket : data_) {
    if (!bucket.empty()) {
      return bucket.begin();
    }
  }
  return data_.back().end();
}

template<typename Key, typename Value>
typename UnorderedMap<Key, Value>::const_iterator UnorderedMap<Key, Value>::end() const 
{
  return data_.back().end();
}

template<typename Key, typename Value>
Value* UnorderedMap<Key, Value>::find(const Key& k) 
{  
  size_t index = hashFunction(k);

  for (auto& pair : data_[index])
  {
    if (pair.first == k)
    {
      return &pair.second;
    }
  }

  return nullptr;
}

template <typename Key, typename Value>
Value& UnorderedMap<Key, Value>::operator[](const Key& k)
{
  size_t index = hashFunction(k);

  for (auto& pair : data_[index])
  {
    if (pair.first == k)
    {
      return pair.second;
    }
  }

  size_++;
  data_[index].push_back(std::make_pair(k, Value()));
  return data_[index].back().second;
}

template <typename Key, typename Value>
std::string UnorderedMap<Key, Value>::toString()
{
  std::ostringstream oss;
  bool firstElement = true;

  for (const auto& bucket : data_)
  {
    for (const auto& pair : bucket)
    {
      if (!firstElement)
      {
        oss << ", ";
      }
      oss << "(" << pair.first << ", " << pair.second << ")";
      firstElement = false;
    }
  }

  return oss.str();
}

template<typename Key, typename Value>
bool UnorderedMap<Key, Value>::isEmpty() 
{
  return size_ == 0;
}

template<typename Key, typename Value>
size_t UnorderedMap<Key, Value>::size() 
{
  return size_;
}

template<typename Key, typename Value>
void UnorderedMap<Key, Value>::clear() 
{
  for (auto& bucket : data_) {
    bucket.clear();
  }
  size_ = 0;
}

template<typename Key, typename Value>
size_t UnorderedMap<Key, Value>::hashFunction(const Key& k) {
  return std::hash<Key>{}(k) % NUMBER_OF_INDEX;
}

} // namespace DSA

#endif // UNORDEREDMAP_H