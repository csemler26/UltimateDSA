# Map Design Document

## Overview

`std::map` is an ordered associative container that stores key-value pairs in a balanced binary search tree (typically a red-black tree). It provides logarithmic time complexity for insertion, deletion, and lookup operations while maintaining elements in sorted order by key.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Data Structure Layout

```
std::map<Key, Value> Memory Layout:

Tree Structure (Red-Black Tree):
        ┌─────────────┐
        │   Root      │
        │   Node      │
        └─────┬───────┘
              │
        ┌─────┴─────┐
        │           │
    ┌───┴───┐   ┌───┴───┐
    │ Left  │   │Right  │
    │ Child │   │Child │
    └───────┘   └───────┘

Each Node Structure:
┌─────────────────────────────────┐
│ Node                            │
├─────────────────────────────────┤
│ key: Key                        │
│ value: Value                    │
│ color: bool (red/black)         │
│ parent: Node*                   │
│ left: Node*                     │
│ right: Node*                    │
└─────────────────────────────────┘
```

### 2. Ordering and Balancing

- **Red-Black Tree Properties:**
  - Every node is either red or black
  - Root is always black
  - Red nodes cannot have red children (no two consecutive red nodes)
  - Every path from root to leaf has the same number of black nodes
  - All leaves are black (null nodes)

## Operations

### Insert Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `insert(pair)` | O(log n) | Inserts key-value pair, maintains order |
| `insert_or_assign()` | O(log n) | Inserts or updates existing key |
| `emplace()` | O(log n) | Constructs element in-place |
| `operator[]` | O(log n) | Access operator (inserts default if key missing) |

### Access Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `find(key)` | O(log n) | Returns iterator to element or end() |
| `at(key)` | O(log n) | Access with bounds checking |
| `operator[]` | O(log n) | Direct access (may insert default) |
| `lower_bound(key)` | O(log n) | First element >= key |
| `upper_bound(key)` | O(log n) | First element > key |

### Erase Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `erase(key)` | O(log n) | Removes element by key |
| `erase(iterator)` | O(log n) | Removes element at iterator |
| `erase(range)` | O(log n) | Removes range of elements |

## Memory Management

- **Node-based:** Each key-value pair is stored in a separate node
- **Dynamic allocation:** Each insertion requires heap allocation for new nodes
- **Automatic cleanup:** Destructor handles deallocation of all nodes
- **No reallocation:** Unlike vectors, maps don't need to resize underlying storage

## Usage Examples

```cpp
#include <map>
#include <string>
#include <iostream>

std::map<std::string, int> scores;

// Insert elements
scores["Alice"] = 95;
scores.insert({"Bob", 87});
scores.emplace("Charlie", 92);

// Access elements
std::cout << "Alice's score: " << scores["Alice"] << std::endl;
std::cout << "Bob's score: " << scores.at("Bob") << std::endl;

// Iterate (in sorted order)
for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}

// Find elements
auto it = scores.find("Alice");
if (it != scores.end()) {
    std::cout << "Found: " << it->first << " = " << it->second << std::endl;
}
```

## Performance Characteristics

### Best Case
- All operations: O(log n) - balanced tree operations

### Average Case
- All operations: O(log n) - tree maintains balance through rotations

### Worst Case
- All operations: O(log n) - red-black tree guarantees logarithmic performance

## Memory Overhead

- **Per-element:** 3 pointers (parent, left, right) + color bit + key + value
- **Container overhead:** Root pointer + size counter
- **Total per element:** Typically 24-32 bytes + sizeof(Key) + sizeof(Value)

## Comparison with Other Containers

| Container | Ordering | Lookup | Insert | Memory |
|-----------|----------|--------|--------|--------|
| `std::map` | Sorted | O(log n) | O(log n) | High |
| `std::unordered_map` | None | O(1) avg | O(1) avg | Medium |
| `std::set` | Sorted | O(log n) | O(log n) | Medium |

## Use Cases

- **Ordered data:** When you need keys in sorted order
- **Range queries:** Finding elements within key ranges
- **Dictionaries:** Key-value storage with automatic sorting
- **Symbol tables:** Where order matters (compilers, databases)

## Known Limitations

- No random access by index (only by key)
- Higher memory overhead than unordered containers
- Slower than hash-based containers for large datasets
- Iterator invalidation on modifications