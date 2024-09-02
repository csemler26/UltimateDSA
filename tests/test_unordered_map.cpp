#include <cassert>
#include <iostream>

#include "unordered_map.h"

// ANSI color codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[35m"
#define MAGENTA "\033[36m"
#define RESET "\033[0m"

using namespace DSA;

#define CHECK(cond) checkCondition((cond), __FILE__, __LINE__)

// Helper function to check conditions and print error messages
bool checkCondition(bool condition, const std::string& functionName, const int& lineNum)
{
  if (!condition)
  {
    std::cerr << RED << "Error" << RESET << " in " << MAGENTA << functionName << RESET << " at "
              << BLUE << "line " << lineNum << RESET << std::endl;
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

  passed &= CHECK(map.find(1) != nullptr && *map.find(1) == "one");
  passed &= CHECK(map.find(2) != nullptr && *map.find(2) == "two");
  passed &= CHECK(map.find(3) != nullptr && *map.find(3) == "three");
  passed &= CHECK(map.find(4) == nullptr);

  passed &= CHECK(map[1] == "one");
  passed &= CHECK(map[2] == "two");
  passed &= CHECK(map[3] == "three");
  passed &= CHECK(map[4] == "");

  return passed;
}

bool testErase()
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.insert(3, "three");

  passed &= CHECK(map.erase(2));
  passed &= CHECK(map.find(2) == nullptr);
  passed &= CHECK(!map.erase(2));

  return passed;
}

bool testUpdateValue()
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  map.insert(2, "two_updated");

  passed &= CHECK(map.find(2) != nullptr && *map.find(2) == "two");

  return passed;
}

bool testComplexKeys()
{
  bool passed = true;

  UnorderedMap<std::string, int> map;
  map.insert("one", 1);
  map.insert("two", 2);
  map.insert("three", 3);

  passed &= CHECK(map.find("one") != nullptr && *map.find("one") == 1);
  passed &= CHECK(map.find("two") != nullptr && *map.find("two") == 2);
  passed &= CHECK(map.find("three") != nullptr && *map.find("three") == 3);
  passed &= CHECK(map.find("four") == nullptr);

  return passed;
}

bool testSizeAndEmpty()
{
  bool passed = true;

  UnorderedMap<int, std::string> map;

  passed &= CHECK(map.isEmpty());
  passed &= CHECK(map.size() == 0);

  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  passed &= CHECK(!map.isEmpty());
  passed &= CHECK(map.size() == 3);

  passed &= CHECK(map.erase(2));
  passed &= CHECK(!map.isEmpty());
  passed &= CHECK(map.size() == 2);

  return passed;
}

bool testToString()
{
  bool passed = true;

  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  passed &= CHECK(map.toString() == "(1, one), (2, two), (3, three)");

  map.erase(2);
  passed &= CHECK(map.toString() == "(1, one), (3, three)");

  return passed;
}

bool testIterator()
{
  bool passed = true;
  UnorderedMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map[3] = "three";

  passed &= CHECK(map.begin() != map.end());

  auto it = map.begin();
  passed &= CHECK(it->first == 1);
  ++it;
  passed &= CHECK(it->first == 2);

  map.clear();
  passed &= CHECK(map.size() == 0);
  passed &= CHECK(map.begin() == map.end());

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
    std::cout << GREEN << "All unordered_map tests passed!" << RESET << std::endl;
  }
  else
  {
    std::cout << YELLOW << "Unorded_map tests failed." << RESET << std::endl;
  }

  return 0;
}