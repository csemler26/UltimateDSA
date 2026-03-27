# Set Design Document

## Overview

`std::set` is an ordered associative container that stores unique keys in a balanced binary search tree (typically a red-black tree). It provides logarithmic time complexity for insertion, deletion, and lookup operations while maintaining elements in sorted order.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Data Structure Layout

```
std::set<Key> Memory Layout:

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
| `insert(key)` | O(log n) | Inserts key if it doesn't exist |
| `emplace()` | O(log n) | Constructs element in-place |
| `emplace_hint()` | O(log n) | Hint for insertion position |

### Access Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `find(key)` | O(log n) | Returns iterator to element or end() |
| `count(key)` | O(log n) | Returns 0 or 1 |
| `contains(key)` | O(log n) | C++20: checks existence |
| `lower_bound(key)` | O(log n) | First element >= key |
| `upper_bound(key)` | O(log n) | First element > key |

### Erase Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `erase(key)` | O(log n) | Removes element by key |
| `erase(iterator)` | O(log n) | Removes element at iterator |
| `erase(range)` | O(log n) | Removes range of elements |
| `clear()` | O(n) | Removes all elements |

## Memory Management

- **Node-based:** Each key is stored in a separate node
- **Dynamic allocation:** Each insertion requires heap allocation for new nodes
- **Automatic cleanup:** Destructor handles deallocation of all nodes
- **No reallocation:** Unlike vectors, sets don't need to resize underlying storage

## Usage Examples

```cpp
#include <set>
#include <string>
#include <iostream>

std::set<std::string> unique_names;

// Insert elements
unique_names.insert("Alice");
unique_names.insert("Bob");
unique_names.emplace("Charlie");
unique_names.insert("Alice");  // Duplicate, not inserted

// Check membership
if (unique_names.contains("Alice")) {
    std::cout << "Alice is in the set" << std::endl;
}

// Iterate (in sorted order)
for (const auto& name : unique_names) {
    std::cout << name << std::endl;
}

// Find elements
auto it = unique_names.find("Bob");
if (it != unique_names.end()) {
    std::cout << "Found: " << *it << std::endl;
}

// Range queries
auto lower = unique_names.lower_bound("B");
auto upper = unique_names.upper_bound("C");
std::cout << "Names starting with 'B': ";
for (auto it = lower; it != upper; ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl;

// Set operations
std::set<int> set1 = {1, 2, 3, 4, 5};
std::set<int> set2 = {3, 4, 5, 6, 7};

// Union
std::set<int> union_set;
std::set_union(set1.begin(), set1.end(),
               set2.begin(), set2.end(),
               std::inserter(union_set, union_set.begin()));

// Intersection
std::set<int> intersection_set;
std::set_intersection(set1.begin(), set1.end(),
                     set2.begin(), set2.end(),
                     std::inserter(intersection_set, intersection_set.begin()));
```

## Performance Characteristics

### Best Case
- All operations: O(log n) - balanced tree operations

### Average Case
- All operations: O(log n) - tree maintains balance through rotations

### Worst Case
- All operations: O(log n) - red-black tree guarantees logarithmic performance

## Memory Overhead

- **Per-element:** 3 pointers (parent, left, right) + color bit + key
- **Container overhead:** Root pointer + size counter
- **Total per element:** Typically 20-28 bytes + sizeof(Key)

## Comparison with Other Containers

| Container | Ordering | Lookup | Insert | Memory | Uniqueness |
|-----------|----------|--------|--------|--------|------------|
| `std::set` | Sorted | O(log n) | O(log n) | Medium | Yes |
| `std::unordered_set` | None | O(1) avg | O(1) avg | Low | Yes |
| `std::map` | Sorted | O(log n) | O(log n) | High | Keys only |

## Use Cases

- **Ordered unique collections:** When you need sorted unique elements
- **Set operations:** Mathematical set operations (union, intersection, difference)
- **Range queries:** Finding elements within key ranges
- **Deduplication:** Removing duplicates while maintaining order
- **Ordered data processing:** Where iteration order matters

## Known Limitations

- No random access by index (only by key)
- Higher memory overhead than unordered containers
- Slower than hash-based containers for large datasets
- Iterator invalidation on modifications