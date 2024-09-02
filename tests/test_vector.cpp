#include <cassert>
#include <iostream>

#include "vector.h"

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
    std::cerr << RED << "Error" << RESET << " in " << MAGENTA << functionName << RESET
              << " at line " << BLUE << lineNum << RESET << std::endl;
  }
  return condition;
}

bool testPushBackAndPopBack()
{
  bool passed = true;

  Vector<int> vec;

  vec.push_back(0);
  vec.push_back(1);

  passed &= CHECK(vec.find(0) != nullptr && *vec.find(0) == 0);
  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) == 1);
  passed &= CHECK(vec.toString() == "[0, 1]");
  passed &= CHECK(vec.find(2) == nullptr);

  passed &= CHECK(vec[0] == 0);
  passed &= CHECK(vec[1] == 1);

  vec.pop_back();
  passed &= CHECK(vec.find(0) != nullptr && *vec.find(0) == 0);
  passed &= CHECK(vec.find(1) == nullptr);
  passed &= CHECK(vec.toString() == "[0]");
  passed &= CHECK(vec.find(2) == nullptr);

  passed &= CHECK(vec[0] == 0);
  passed &= CHECK(vec[1] != 1);

  vec.pop_back();
  passed &= CHECK(vec.find(0) == nullptr);
  passed &= CHECK(vec.toString() == "[]");
  passed &= CHECK(vec[0] != 0);

  return passed;
}

bool testInsertAndFind()
{
  bool passed = true;

  Vector<int> vec;

  vec.insert(0, 0);
  vec.insert(1, 1);

  passed &= CHECK(vec.find(0) != nullptr && *vec.find(0) == 0);
  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) == 1);
  passed &= CHECK(vec.find(2) == nullptr);

  passed &= CHECK(vec[0] == 0);
  passed &= CHECK(vec[1] == 1);

  return passed;
}

bool testErase()
{
  bool passed = true;

  Vector<int> vec;
  vec.insert(0, 0);
  vec.insert(1, 1);
  vec.insert(2, 2);

  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) == 1);
  passed &= CHECK(vec.find(2) != nullptr && *vec.find(2) == 2);
  passed &= CHECK(vec.erase(1));
  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) != 1);
  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) == 2);
  passed &= CHECK(vec.find(2) == nullptr);

  return passed;
}

bool testUpdateValue()
{
  bool passed = true;

  Vector<int> vec;
  vec.push_back(0);
  vec.push_back(1);

  vec.insert(1, 10);
  vec[0] = 100;

  passed &= CHECK(vec.find(0) != nullptr && *vec.find(0) == 100);
  passed &= CHECK(vec[0] == 100);
  passed &= CHECK(vec.find(1) != nullptr && *vec.find(1) == 10);
  passed &= CHECK(vec[1] == 10);

  return passed;
}

bool testSizeAndEmpty()
{
  bool passed = true;

  Vector<int> vec;

  passed &= CHECK(vec.isEmpty());
  passed &= CHECK(vec.size() == 0);

  vec.push_back(0);
  vec.push_back(1);
  vec.push_back(2);

  passed &= CHECK(!vec.isEmpty());
  passed &= CHECK(vec.size() == 3);

  passed &= CHECK(vec.erase(2));
  passed &= CHECK(!vec.isEmpty());
  passed &= CHECK(vec.size() == 2);

  return passed;
}

bool testToString()
{
  bool passed = true;

  Vector<int> vec;

  vec.push_back(0);
  vec.push_back(1);
  vec.push_back(2);

  passed &= CHECK(vec.toString() == "[0, 1, 2]");

  vec.erase(2);
  passed &= CHECK(vec.toString() == "[0, 1]");

  vec.erase(0);
  passed &= CHECK(vec.toString() == "[1]");

  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  passed &= CHECK(vec.toString() == "[1, 3, 4, 5]");

  vec[0] = 0;
  passed &= CHECK(vec.toString() == "[0, 3, 4, 5]");

  vec.pop_back();
  passed &= CHECK(vec.toString() == "[0, 3, 4]");

  return passed;
}

bool testClear()
{
  bool passed = true;

  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec[2] = 3;

  vec.clear();
  passed &= CHECK(vec.isEmpty());
  passed &= CHECK(vec.size() == 0);

  return passed;
}

bool testCapacity()
{
  bool passed = true;

  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec[2] = 3;

  passed &= CHECK(vec.capacity() >= vec.size());

  return passed;
}

int main()
{
  bool allPassed = true;

  allPassed &= testInsertAndFind();
  allPassed &= testErase();
  allPassed &= testUpdateValue();
  allPassed &= testSizeAndEmpty();
  allPassed &= testToString();
  allPassed &= testClear();
  allPassed &= testCapacity();

  if (allPassed)
  {
    std::cout << GREEN << "All vector tests passed!" << RESET << std::endl;
  }
  else
  {
    std::cout << YELLOW << "Vector tests failed." << RESET << std::endl;
  }

  return 0;
}