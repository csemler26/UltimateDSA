#include "unordered_map.h"
#include <iostream>
#include <cassert>

using namespace DSA;

void testInsertAndFind() {
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  assert(map.find(1) != nullptr && *map.find(1) == "one");
  assert(map.find(2) != nullptr && *map.find(2) == "two");
  assert(map.find(3) != nullptr && *map.find(3) == "three");
  assert(map.find(4) == nullptr);

  assert(map[1] == "one");
  assert(map[2] == "two");
  assert(map[3] == "three");
  assert(map[4] == "");
}

void testErase() {
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.insert(3, "three");

  assert(map.erase(2));
  assert(map.find(2) == nullptr);

  assert(!map.erase(2));
}

void testUpdateValue() {
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  map.insert(2, "two_updated");

  assert(map.find(2) != nullptr && *map.find(2) == "two");
}

void testComplexKeys() {
  UnorderedMap<std::string, int> map;
  map.insert("one", 1);
  map.insert("two", 2);
  map.insert("three", 3);

  assert(map.find("one") != nullptr && *map.find("one") == 1);
  assert(map.find("two") != nullptr && *map.find("two") == 2);
  assert(map.find("three") != nullptr && *map.find("three") == 3);
  assert(map.find("four") == nullptr);
}

void testSizeAndEmpty() {
  UnorderedMap<int, std::string> map;

  assert(map.isEmpty());
  assert(map.size() == 0);

  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";
  
  assert(!map.isEmpty());
  assert(map.size() == 3);
  
  assert(map.erase(2));
  assert(!map.isEmpty());
  assert(map.size() == 2);
}

void testToString() {
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  assert(map.toString() == "(1, one), (2, two), (3, three)");

  map.erase(2);
  assert(map.toString() == "(1, one), (3, three)");
}

int main() {
  testInsertAndFind();
  testErase();
  testUpdateValue();
  testComplexKeys();
  testSizeAndEmpty();
  testToString();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}