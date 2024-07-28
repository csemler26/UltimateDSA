#include "unordered_map.h"
#include <iostream>
#include <cassert>

using namespace DSA;

// Helper function to check conditions and print error messages
bool checkCondition(bool condition, const std::string& functionName, const int& lineNum) 
{
  if (!condition) {
    std::cerr << "\033[31mError \033[0min \033[36m" << functionName << "\033[0m at \033[35mline " << lineNum << "\033[0m" << std::endl;
  }
  return condition;
}

bool testInsertAndFind() 
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";
  
  passed &= checkCondition(map.find(1) != nullptr && *map.find(1) == "one", __FILE__, __LINE__);
  passed &= checkCondition(map.find(2) != nullptr && *map.find(2) == "two", __FILE__, __LINE__);
  passed &= checkCondition(map.find(3) != nullptr && *map.find(3) == "three", __FILE__, __LINE__);
  passed &= checkCondition(map.find(4) == nullptr, __FILE__, __LINE__);

  passed &= checkCondition(map[1] == "one", __FILE__, __LINE__);
  passed &= checkCondition(map[2] == "two", __FILE__, __LINE__);
  passed &= checkCondition(map[3] == "three", __FILE__, __LINE__);
  passed &= checkCondition(map[4] == "", __FILE__, __LINE__);

  return passed;
}

bool testErase() 
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.insert(3, "three");

  passed &= checkCondition(map.erase(2), __FILE__, __LINE__);
  passed &= checkCondition(map.find(2) == nullptr, __FILE__, __LINE__);
  passed &= checkCondition(!map.erase(2), __FILE__, __LINE__);

  return passed;
}

bool testUpdateValue() 
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  map.insert(2, "two_updated");

  passed &= checkCondition(map.find(2) != nullptr && *map.find(2) == "two", __FILE__, __LINE__);

  return passed;
}

bool testComplexKeys() 
{
  bool passed = true;

  UnorderedMap<std::string, int> map;
  map.insert("one", 1);
  map.insert("two", 2);
  map.insert("three", 3);

  passed &= checkCondition(map.find("one") != nullptr && *map.find("one") == 1, __FILE__, __LINE__);
  passed &= checkCondition(map.find("two") != nullptr && *map.find("two") == 2, __FILE__, __LINE__);
  passed &= checkCondition(map.find("three") != nullptr && *map.find("three") == 3, __FILE__, __LINE__);
  passed &= checkCondition(map.find("four") == nullptr, __FILE__, __LINE__);

  return passed;
}

bool testSizeAndEmpty() 
{
  bool passed = true;

  UnorderedMap<int, std::string> map;

  passed &= checkCondition(map.isEmpty(), __FILE__, __LINE__);
  passed &= checkCondition(map.size() == 0, __FILE__, __LINE__);

  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";
  
  passed &= checkCondition(!map.isEmpty(), __FILE__, __LINE__);
  passed &= checkCondition(map.size() == 3, __FILE__, __LINE__);
  
  passed &= checkCondition(map.erase(2), __FILE__, __LINE__);
  passed &= checkCondition(!map.isEmpty(), __FILE__, __LINE__);
  passed &= checkCondition(map.size() == 2, __FILE__, __LINE__);

  return passed;
}

bool testToString() 
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  passed &= checkCondition(map.toString() == "(1, one), (2, two), (3, three)", __FILE__, __LINE__);

  map.erase(2);
  passed &= checkCondition(map.toString() == "(1, one), (3, three)", __FILE__, __LINE__);

  return passed;
}

bool testIterator() 
{
  bool passed = true;
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  passed &= checkCondition(map.begin() != map.end(), __FILE__, __LINE__);
  map.clear();
  passed &= checkCondition(map.begin() == map.end(), __FILE__, __LINE__);

  return passed;
}

int main() 
{
  bool allPassed = true;
 
  allPassed &= testInsertAndFind();
  allPassed &= testErase();
  allPassed &= testUpdateValue();
  allPassed &= testComplexKeys();
  allPassed &= testSizeAndEmpty();
  allPassed &= testToString();
  allPassed &= testIterator();

  if (allPassed)
  {
    std::cout << "\033[32mAll unordered_map tests passed!\033[0m" << std::endl;
  }
  else
  {
    std::cout << "\033[31mUnorded_map tests failed.\033[0m" << std::endl;
  }

  return 0;
}