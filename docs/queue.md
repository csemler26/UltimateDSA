# Queue Design Document

## Overview

A `queue` is a data structure that operates on a **FIFO** (First-In, First-Out) basis.

## Standard Library
- In the standard template library, the std::queue is an *adapter*, meaning its memory layout depends entirely on the underlying container it uses.  
  - By default, it uses a **std::deque** (double ended queue)
    - ```std::queue<int> q;```
    - Hybrid between a **std::vector** (one, solid block of memory) and a **std::list** (nodes scattered everywhere)
    - Maintains a "map" of pointers that point to several fixed-size arrays (chunks) of memory
    - Allows the queue to:
      - Grow dynamically
      - Without reallocating the entire dataset
      - While maintaining decent cache locality (better than a list)
  - Alternative, can select a **std::list** (linked list)
    - ```std::queue<int, std::list<int>> q;```
    - std::queue must be forced to use std::list
    - Each element is a separate heap allocation, linked by pointers

### Pros and Cons

| Feature | Pros | Cons |
|-----------|-----------------|-------|
| **Access** | Strict discipline (you cannot accidentally modify elements in the middle of the queue) | No Random Access (you cannot access the 5th element without popping the first 4. iterating over a queue is not supported directly) | 
| **Performance** | O(1) complexity for push (insertion) and pop (deletion) | Slight memory overhead due to the container adapter structure compare to raw arrays | 
| **Memory** | Dynamic sizing (it grows as needed) | If using std::list, there is a high memory overhead per element (pointers). If using std::deque, memory is allocated in chunks, which can be unused if the queue is small | 

### Basic Operations
```cpp
push(val) // inserts element val at the back
pop() // removes the element from the front
front() // returns a reference to the element at the front
back() // returns a reference to the element at the back
empty() // returns true if the queue has no elements
size() // returns the number of elements 
```

### Example
```cpp
std::queue<std::string> customerLine;

customerLine.push("Alice");
customerLine.push("Bob");
customerLine.push("Charlie");

std::cout << "First in line: " << customerLine.front() << "\n"; // Outputs Alice
std::cout << "Last in line: " << customerLine.back() << "\n";   // Outputs Charlie

while (!customerLine.empty()) 
{
  std::string currentPerson = customerLine.front();
  std::cout << "Serving: " << currentPerson << "\n";
  customerLine.pop();
}
```

### Use Cases
- **Breadth-First Search (BFS)**: in graph algorithms, queues are essential to explore neighbor nodes before moving deeper
- **Task Scheduling**: Managing printer jobs, CPU task scheduling, or web server requests where fairness (first come, first served) is required
- **Buffering**: Handling data streams (like IO buffers) where data arrives asynchronously and must be processed in order

### Advanced Variations
- **std::priority_queue**: This is NOT FIFO. It automatically sorts elements so that the "largest" (or highest priority) element is always at the front
  - Often implemented using a Heap structure


## Underlying Container Comparison

### Circular Buffer
- The high-performance choice
- Not a standard STL container but is arguably the most important data structure for systems programming
- Uses a fixed-size **std::array** or **std::vector** and two integers (head and tail indices) that wrap around using modulo arithmetic
- **Pros**
  - No allocation: once created, it never calls new or malloc
  - Perfect cache locality: it is a single contiguous block of memory
  - Thread safety: it is easier to make a "wait-free" single-producer/single-consumer queue using a ring buffer than any other structure
- **Cons**
  - Fixed size: if the queue fills up, you must either drop data (lossy) or blocks the producer (wait). Resizing circular buffer is expensive and complex
- **When to use**
  - When latency is critical
  - Inter-thread communication: passing messages between a UI thread and a background worker
  - Embedded systems: where heap allocation is forbidden

### std::deque
- The default container for **std::queue** 
- Strikes the best balance for general-purpose computing
- Allocates memory in "pages" or chunks, linked by a central directory
- **Pros**
  - Fast expansion: can grow in both directions without copying existing data to a new location
  - Good cache locality
- **Cons**
  - Blocked overhead: manages a map of pointers to these chunks, which adds slight overhead compared to a raw array
- **When to use**
  - Safe choice for queues

### std::list
- **Pros**
  - Iterator/pointer stability: if you have a pointer to an element inside the queue, that pointer remains valid even if you push/pop other elements
  - Cheap slicing: you can move large sections of one queue to another just by swapping pointers, without copying the data
- **Cons**
  - Cache thrashing: Every element is a separate heap allocation. Traversing or processing the queue, causes constant "cache misses" because nodes are scattered in RAM
  - Memory overhead: Every element requires extra memory for *prev* and *next* pointers
- **When to use**
  - When the objects stored are very large/expensive to copy
  - When you need to merge queues frequently
  - When external observers hold pointers to queue elements

