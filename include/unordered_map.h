#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <functional>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace DSA
{

const size_t NUMBER_OF_INDEX = 10;

template <typename Key, typename Value>
class UnorderedMap
{
 public:
  using PairType = std::pair<Key, Value>;
  using ListType = std::list<PairType>;
  using VecType = std::vector<ListType>;

  class UnorderedMapIterator
  {
   public:
    using vec_iter = typename VecType::iterator;
    using list_iter = typename ListType::iterator;

    UnorderedMapIterator(vec_iter v_it, vec_iter v_end) : vec_it(v_it), vec_end(v_end)
    {
      if (vec_it != vec_end)
      {
        list_it = vec_it->begin();
        skipEmptyBuckets();
      }
    }

    std::pair<Key, Value>& operator*() { return *list_it; }

    PairType* operator->() { return &(*list_it); }

    UnorderedMapIterator& operator++()
    {
      ++list_it;
      if (list_it == vec_it->end())
      {
        ++vec_it;
        if (vec_it != vec_end)
        {
          list_it = vec_it->begin();
        }
      }
      skipEmptyBuckets();
      return *this;
    }

    bool operator!=(const UnorderedMapIterator& other) const { return !(*this == other); }

    bool operator==(const UnorderedMapIterator& other) const
    {
      return vec_it == other.vec_it && list_it == other.list_it;
    }

   private:
    vec_iter vec_it;
    vec_iter vec_end;
    list_iter list_it;

    void skipEmptyBuckets()
    {
      while (vec_it != vec_end && list_it == vec_it->end())
      {
        ++vec_it;
        if (vec_it != vec_end)
        {
          list_it = vec_it->begin();
        }
      }
    }
  };

  UnorderedMap();
  ~UnorderedMap();
  bool insert(const Key& k, const Value& v);
  bool erase(const Key& k);

  UnorderedMapIterator begin() { return UnorderedMapIterator(data_.begin(), data_.end()); }

  UnorderedMapIterator end() { return UnorderedMapIterator(data_.end(), data_.end()); }

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

template <typename Key, typename Value>
UnorderedMap<Key, Value>::UnorderedMap()
    : data_(NUMBER_OF_INDEX, std::list<std::pair<Key, Value>>()), size_(0)
{
}

template <typename Key, typename Value>
UnorderedMap<Key, Value>::~UnorderedMap()
{
}

template <typename Key, typename Value>
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

template <typename Key, typename Value>
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

template <typename Key, typename Value>
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

template <typename Key, typename Value>
bool UnorderedMap<Key, Value>::isEmpty()
{
  return size_ == 0;
}

template <typename Key, typename Value>
size_t UnorderedMap<Key, Value>::size()
{
  return size_;
}

template <typename Key, typename Value>
void UnorderedMap<Key, Value>::clear()
{
  for (auto& bucket : data_)
  {
    bucket.clear();
  }
  data_.clear();
  size_ = 0;
}

template <typename Key, typename Value>
size_t UnorderedMap<Key, Value>::hashFunction(const Key& k)
{
  return std::hash<Key>{}(k) % NUMBER_OF_INDEX;
}

}  // namespace DSA

#endif  // UNORDEREDMAP_H