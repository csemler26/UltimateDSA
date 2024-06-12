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
  UnorderedMap();
  ~UnorderedMap();
  bool insert (const Key& k, const Value& v);
  bool erase(const Key& k);
  
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

} // namespace DSA

#endif // UNORDEREDMAP_H