#include <cassert>
#include <iostream>

#include "sharedPtr.h"

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

struct MyObject {
  MyObject(int v) : value(v) {}
  void show() { std::cout << "Value: " << value << "\n"; }
  int value;
};

bool testConstructors()
{
  bool passed = true;

  SharedPtr<MyObject> ptr1 = makeShared<MyObject>(42);
  passed &= CHECK(ptr1.useCount() == 1);

  // Copy 
  SharedPtr<MyObject> ptr2 = ptr1;
  passed &= CHECK(ptr1.useCount() == 2);

  // Move constructor
  SharedPtr<MyObject> ptr3(std::move(ptr1));
  passed &= CHECK(ptr3.useCount() == 2);
  passed &= CHECK(ptr1.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 2);

  // Move assignment
  SharedPtr<MyObject> ptr4 = std::move(ptr3);
  passed &= CHECK(ptr4.useCount() == 2);
  passed &= CHECK(ptr3.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 2);

  // Reset
  ptr4.reset();
  passed &= CHECK(ptr4.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 1);
  
  return passed;
}

bool testUseCount()
{
  bool passed = true;

  SharedPtr<MyObject> ptr1 = makeShared<MyObject>(42);
  passed &= CHECK(ptr1.useCount() == 1);

  // Copy 
  SharedPtr<MyObject> ptr2 = ptr1;
  passed &= CHECK(ptr1.useCount() == 2);

  // Move constructor
  SharedPtr<MyObject> ptr3(std::move(ptr1));
  passed &= CHECK(ptr3.useCount() == 2);
  passed &= CHECK(ptr1.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 2);

  // Move assignment
  SharedPtr<MyObject> ptr4 = std::move(ptr3);
  passed &= CHECK(ptr4.useCount() == 2);
  passed &= CHECK(ptr3.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 2);

  // Reset
  ptr4.reset();
  passed &= CHECK(ptr4.useCount() == 0);
  passed &= CHECK(ptr2.useCount() == 1);

  return passed;
}

int main()
{
  bool allPassed = true;
  
  allPassed &= testConstructors();
  allPassed &= testUseCount();

  if (allPassed)
  {
    std::cout << GREEN << "All sharedPtr tests passed!" << RESET << std::endl;
  }
  else
  {
    std::cout << YELLOW << "sharedPtr tests failed." << RESET << std::endl;
  }

  return 0;
}