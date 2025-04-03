#include <cassert>
#include <iostream>
#include <thread>

#include "stockPriceQueue.h"

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

bool testPush()
{
  bool passed = true;

  StockPriceQueue<10> queue;

  queue.push("TSLA", 100.0);

  passed &= CHECK(queue.getPrice("TSLA") == 100.0);

  return passed;
}

int main()
{
  bool allPassed = true;
  
  allPassed &= testPush();
  // allPassed &= testEnqueue();

  if (allPassed)
  {
    std::cout << GREEN << "All StockPriceQueue tests passed!" << RESET << std::endl;
  }
  else
  {
    std::cout << YELLOW << "StockPriceQueue tests failed." << RESET << std::endl;
  }

  return 0;
}