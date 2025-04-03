#include <cassert>
#include <iostream>
#include <thread>

#include "spinLock.h"

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

SpinLock sLock;
int value = 0;

void tempTask1(size_t count)
{
  for (size_t i = 0; i < count; ++i)
  {
    sLock.lock();
    value++;
    sLock.unlock();
  }
}

bool testLock()
{
  bool passed = true;

  passed &= CHECK(value == 0);

  std::thread thread1(tempTask1, 1500);
  std::thread thread2(tempTask1, 2750);

  thread1.join();
  thread2.join();

  passed &= CHECK(value == 4250);

  return passed;
}

int main()
{
  bool allPassed = true;
  
  allPassed &= testLock();

  if (allPassed)
  {
    std::cout << GREEN << "All SpinLock tests passed!" << RESET << std::endl;
  }
  else
  {
    std::cout << YELLOW << "SpinLock tests failed." << RESET << std::endl;
  }

  return 0;
}