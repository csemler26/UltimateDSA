# Unordered Set Design Document

## Overview

`std::unordered_set` is an unordered associative container that stores unique keys in a hash table. It provides average constant-time complexity for insertion, deletion, and lookup operations, storing only keys without associated values.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Data Structure Layout

```
std::unordered_set<Key> Memory Layout:

Hash Table Structure:
┌─────────────────────────────────┐
│ Hash Table Control Block        │
├─────────────────────────────────┤
│ buckets: Bucket*                │  <- Array of bucket pointers
│ size: size_t                    │  <- Number of elements
│ bucket_count: size_t            │  <- Number of buckets
│ load_factor: float              │  <- Current load factor
│ max_load_factor: float          │  <- Maximum load factor
└─────────────────────────────────┘
          │
          ▼
    ┌─────┬─────┬─────┬─────┬─────┐
    │Bkt0 │Bkt1 │Bkt2 │Bkt3 │Bkt4 │  <- Bucket array
    └─────┼─────┼─────┼─────┼─────┘
          │     │     │     │
          ▼     ▼     ▼     ▼
       ┌──┴──┐  │  ┌──┴──┐  │
       │Node │  │  │Node │  │
       │Key  │  │  │Key  │  │
       └─────┘  │  └─────┘  │
                │           │
             ┌──┴──┐     ┌──┴──┐
             │Node │     │Node │
             │Key  │     │Key  │
             └─────┘     └─────┘

Each Node Structure:
┌─────────────────────────────────┐
│ Hash Node                       │
├─────────────────────────────────┤
│ key: Key                        │
│ hash: size_t                    │  <- Cached hash value
│ next: Node*                     │  <- Next in bucket chain
└─────────────────────────────────┘
```

### 2. Hash Function and Buckets

- **Hash Function:** Converts keys to hash values for bucket assignment
- **Buckets:** Array of linked lists for collision resolution
- **Uniqueness:** Each key appears at most once
- **Load Factor:** Ratio of elements to buckets (controls rehashing)

## Operations

### Insert Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `insert(key)` | O(1) average | Inserts if key doesn't exist |
| `emplace()` | O(1) average | Constructs element in-place |
| `emplace_hint()` | O(1) average | Hint for insertion position |

### Access Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `find(key)` | O(1) average | Returns iterator or end() |
| `count(key)` | O(1) average | Returns 0 or 1 |
| `contains(key)` | O(1) average | C++20: checks existence |

### Erase Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `erase(key)` | O(1) average | Removes by key |
| `erase(iterator)` | O(1) average | Removes at iterator |
| `clear()` | O(n) | Removes all elements |

## Memory Management

- **Bucket Array:** Dynamically allocated array of bucket pointers
- **Node-based:** Each key stored in separate heap-allocated node
- **Automatic Rehashing:** Grows when load factor exceeds max_load_factor
- **Load Factor Control:** Configurable maximum load factor (default 1.0)

## Usage Examples

```cpp
#include <unordered_set>
#include <string>
#include <iostream>

std::unordered_set<std::string> unique_words;

// Insert elements
unique_words.insert("hello");
unique_words.insert("world");
unique_words.emplace("hello");  // Duplicate, not inserted

// Check membership
if (unique_words.contains("hello")) {
    std::cout << "Found 'hello'" << std::endl;
}

// Iterate (order not guaranteed)
for (const auto& word : unique_words) {
    std::cout << word << std::endl;
}

// Find elements
auto it = unique_words.find("world");
if (it != unique_words.end()) {
    std::cout << "Found: " << *it << std::endl;
}

// Set operations
std::unordered_set<int> set1 = {1, 2, 3, 4};
std::unordered_set<int> set2 = {3, 4, 5, 6};

// Note: No direct set operations in unordered_set
// Use algorithms or convert to other containers
```

## Performance Characteristics

### Best Case
- All operations: O(1) - perfect hash distribution, no collisions

### Average Case
- All operations: O(1) - good hash function, reasonable collisions

### Worst Case
- All operations: O(n) - poor hash function, all elements in one bucket

## Memory Overhead

- **Per-element:** 1 pointer (next) + hash value + key
- **Bucket overhead:** Array of pointers (one per bucket)
- **Container overhead:** Control block with counters and factors
- **Total per element:** Typically 12-20 bytes + sizeof(Key)

## Hash Function Requirements

- **Deterministic:** Same key always produces same hash
- **Uniform distribution:** Evenly distributes keys across buckets
- **Fast computation:** Hash calculation should be efficient
- **Avalanche effect:** Small key changes produce large hash changes

## Comparison with Other Containers

| Container | Ordering | Lookup | Insert | Memory | Uniqueness |
|-----------|----------|--------|--------|--------|------------|
| `std::unordered_set` | None | O(1) avg | O(1) avg | Low | Yes |
| `std::set` | Sorted | O(log n) | O(log n) | Medium | Yes |
| `std::unordered_map` | None | O(1) avg | O(1) avg | Medium | Keys only |

## Use Cases

- **Uniqueness checking:** Fast membership testing
- **Deduplication:** Removing duplicates from collections
- **Set operations:** Mathematical set operations (union, intersection)
- **Graph algorithms:** Tracking visited nodes
- **Bloom filters:** Approximate membership testing

## Known Limitations

- **Unpredictable iteration order:** Elements not stored in any particular order
- **Hash collisions:** Can degrade performance in worst case
- **Memory overhead:** Higher than ordered containers
- **Rehashing pauses:** Can cause temporary performance spikes
- **Iterator invalidation:** Rehashing invalidates all iterators
- **No ordering:** Cannot iterate in sorted order