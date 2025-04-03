#ifndef STOCKPRICEQUEUE_H
#define STOCKPRICEQUEUE_H

#include <string>
#include <deque>
#include <unordered_map>
#include <mutex>

namespace DSA
{

struct StockEntry {
  std::string ticker;
  double price;
};

template <size_t maxSize>
class StockPriceQueue 
{
public:
  StockPriceQueue() {}

  void push(const std::string& ticker, double price)
  {
    std::lock_guard<std::mutex> lock(mtx_);

    // if the ticker already exists update the price
    if (priceMap_.find(ticker) != priceMap_.end())
    {
      priceMap_[ticker] = price;
      for (auto& entry : priceQueue_) 
      {
        if (entry.ticker == ticker) {
          entry.price = price;
          break;
        }
      }
      return;
    }
    
    // Add new entry
    priceQueue_.push_back({ticker, price});
    priceMap_[ticker] = price;

    // Maintain max size
    if (priceQueue_.size() > maxSize) 
    {
      priceMap_.erase(priceQueue_.front().ticker);
      priceQueue_.pop_front();
    }
  }

  void pop() 
  {
    std::lock_guard<std::mutex> lock(mtx_);

    if (!priceQueue_.empty())
    {
      priceMap_.erase(priceQueue_.front().ticker);
      priceQueue_.pop_front();
    }
  }

  double getPrice(const std::string& ticker) 
  {
    std::lock_guard<std::mutex> lock(mtx_);

    if (priceMap_.find(ticker) != priceMap_.end())
    {
      return priceMap_.at(ticker);
    }

    return 0.0;
}

private:
  std::deque<StockEntry> priceQueue_; // allows for O(1) pop from front and easy push to back
  std::unordered_map<std::string, double> priceMap_;  // used for O(1) look ups
  std::mutex mtx_;
};

}

#endif  // STOCKPRICEQUEUE_H