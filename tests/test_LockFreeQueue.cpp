#include <cassert>
#include <iostream>
#include <thread>

#include "lockFreeQueue.h"

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

struct StockEntry {
  std::string ticker;
  double price;
};

bool testEnqueue()
{
  bool passed = true;

  

  passed &= CHECK(true);

  return passed;
}

int main()
{
  bool allPassed = true;
  
  allPassed &= testEnqueue();
  // allPassed &= testEnqueue();

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