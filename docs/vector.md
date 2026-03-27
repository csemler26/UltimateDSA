# Vector Design Document

## Overview

The `newVector` is a dynamic array implementation that provides automatic memory management and growth strategies.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Data Structure Layout

```
┌─────────────────────────────────┐
│ Vector Instance                 │
├─────────────────────────────────┤
│ data pointer ────────┐          │
│ size             = 3 │          │
│ capacity         = 8 │          │
└─────────────────────┼──────────┘
                      │
                      ▼
              ┌──┬──┬──┬──┬──┬──┬──┬──┐
              │  │  │  │  │  │  │  │  │
              └──┴──┴──┴──┴──┴──┴──┴──┘
               1  2  3  4  5  6  7  8
              Used portion: 1-3
```

### 2. Growth Strategy

**Document your growth strategy here:**
- What is the growth factor? (e.g., 2x, 1.5x)
- When does growth occur?
- Example: `[1] → [2] → [4] → [8] → [16]...`

## Operations

### Insert/Push Operations

| Operation | Time Complexity | Space | Notes |
|-----------|-----------------|-------|-------|
| `push_back()` | O(1) amortized | O(1) | Constant when capacity exists |
| `insert(pos, val)` | O(n) | O(1) | Must shift elements |
| `emplace_back()` | O(1) amortized | O(1) | Constructs in place |

### Access Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `operator[]` | O(1) | Direct array access |
| `at(index)` | O(1) | With bounds checking |
| `front()` / `back()` | O(1) | Direct pointer arithmetic |

### Memory Management

- **Initial Capacity:** [Document default]
- **Reallocation Strategy:** [Describe when/how reallocation occurs]
- **Deallocation:** [Describe cleanup behavior]

## Usage Examples

```cpp
// Example usage patterns here
newVector<int> vec;
vec.push_back(5);
vec.push_back(10);
```

## Performance Characteristics

### Best Case
- Access: O(1)
- Push (with capacity): O(1)

### Average Case
- Push (amortized): O(1)
- Insert: O(n)

### Worst Case
- Reallocation: O(n) - copying all elements to new buffer

## Memory Overhead

- **Per-element:** [Size overhead]
- **Container overhead:** [Fixed overhead for the vector object]

## Comparison with Standard Library

How does `newVector` compare to `std::vector`?

| Aspect | newVector | std::vector |
|--------|-----------|-------------|
| Performance | | |
| Memory Usage | | |
| Features | | |

## Known Limitations

- [Document any limitations]
- [Known edge cases]

## Future Optimizations

- [ ] [Potential improvements]
- [ ] [Performance enhancements]

---

**Related:** See [Unordered Map Design](./unordered_map.md) for another container type.
