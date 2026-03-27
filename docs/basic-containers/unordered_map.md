# Unordered Map Design Document

## Overview

The `unordered_map` is a hash table implementation providing fast key-value lookups with average O(1) performance.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Hash Table Structure

```
Hash Function
     │
     ▼
   input ─┐
           │
    [0] ──┼─→ [data1] ─→ [data2] ─→ ... (collision chain)
    [1] ──┼─→ [data3] ─→ ...
    [2] ──┼─→ ...
    ...   │
    [n] ──┘
    
Buckets with chaining for collision resolution
```

### 2. Collision Resolution Strategy

**Document your approach:**
- [ ] Chaining (linked list in each bucket)
- [ ] Open addressing (linear probing, quadratic probing, etc.)
- [ ] Cuckoo hashing
- [ ] Double hashing

**Details:** [Describe the strategy]

### 3. Hash Function

```cpp
// Document your hash function here
// - Input requirements
// - Output range
// - Distribution properties
// - Example: hash(key) % bucket_count
```

## Operations

### Core Operations

| Operation | Time Complexity | Space | Notes |
|-----------|-----------------|-------|-------|
| `insert(key, value)` | O(1) average | O(1) | O(n) worst case |
| `find(key)` | O(1) average | O(1) | O(n) worst case |
| `erase(key)` | O(1) average | O(1) | O(n) worst case |
| `operator[]` | O(1) average | O(1) | Creates entry if missing |

## Load Factor & Rehashing

- **Load Factor:** [Document when rehashing occurs]
  - **Formula:** `size / capacity`
  - **Threshold:** [Trigger point for rehashing, e.g., 0.75]
  
- **Rehashing Process:** [Describe how rehashing works]
  - **New Capacity:** [How is new size calculated?]
  - **Cost:** O(n) for full rehash

```
Load Factor Growth:
0.0 ──────────────────────── 0.75 ────> REHASH ──────→ 0.375
                           (Threshold)
```

## Usage Examples

```cpp
// Example usage patterns here
unordered_map<std::string, int> map;
map.insert({"key1", 100});
auto it = map.find("key1");
```

## Performance Characteristics

### Best/Average Case
- All operations: O(1)
- Requires good hash function and appropriate load factor

### Worst Case
- All operations: O(n)
- Occurs when all elements hash to same bucket (poor hash or malicious input)

## Memory Overhead

- **Per-entry:** [Size of hash node]
- **Container overhead:** [Fixed overhead]
- **Collision chain overhead:** [Pointer cost]

## Hash Function Properties

A good hash function should have:
- [ ] Uniform distribution across buckets
- [ ] Fast computation
- [ ] Deterministic (same input → same output)
- [ ] Avalanche effect (small input change → large output change)

**Your implementation:** [Describe properties]

## Comparison with Standard Library

How does `unordered_map` compare to `std::unordered_map`?

| Aspect | Custom | std::unordered_map |
|--------|--------|-------------------|
| Hash Function | | |
| Collision Strategy | | |
| Performance | | |

## Known Limitations

- [ ] [Potential issues with specific input patterns]
- [ ] [Thread safety considerations]
- [ ] [Edge cases]

## Future Optimizations

- [ ] [Improve hash function]
- [ ] [Optimize collision handling]
- [ ] [Better rehashing strategy]

---

**Related:** See [Vector Design](./vector.md) for another container type.
