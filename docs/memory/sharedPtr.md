# Shared Pointer Design Document

## Overview

The `sharedPtr` implements reference-counted smart pointers for automatic memory management, allowing multiple owners of the same resource.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Reference Counting Model

```
┌─────────────────────────┐
│ Shared Pointer Object   │
├─────────────────────────┤
│ data_ptr ─────┐         │
│ ref_count ─┐  │         │
└────────────┼──┼─────────┘
             │  │
             │  ▼
             │  ┌──────────┐
             │  │ RefCount │
             │  │ count=2  │
             │  └──────────┘
             │
             ▼
        ┌──────────┐
        │ Object   │
        │ (data)   │
        └──────────┘

Multiple sharedPtrs → One RefCount → One object
```

### 2. Lifecycle

```
Creation:          ref_count = 1
Copy:              ref_count++
Destruction:       ref_count--
Last destructor:   delete object
```

## Operations

### Core Operations

| Operation | Time Complexity | Thread-Safe | Notes |
|-----------|-----------------|-------------|-------|
| Copy Constructor | O(1) | ⚠️ Atomic | Increment counter |
| Assignment | O(1) | ⚠️ Atomic | Decrement old, increment new |
| Destructor | O(1) | ⚠️ Atomic | Decrement counter |
| `get()` | O(1) | ✅ Yes | Returns raw pointer |
| `use_count()` | O(1) | ✅ Yes | Reads counter |

### Pointer Operations

| Operation | Behavior |
|-----------|----------|
| `operator*` | Dereference object |
| `operator->` | Access object members |
| `operator bool` | Check if valid |
| `reset()` | Release ownership |

## Reference Count Management

### Implementation Approach

**How is the reference count stored?**
- [ ] Embedded in object
- [ ] Separate control block (heap allocated)
- [ ] Intrusive (in user class)

**Details:** [Describe]

### Atomic Operations

```cpp
// Increment on copy
ref_count.fetch_add(1, memory_order_relaxed);

// Decrement on destruction
if (ref_count.fetch_sub(1, memory_order_release) == 1) {
    // Last owner, safe to delete
    delete object;
}
```

**Your memory ordering strategy:** [Describe]

## Ownership Semantics

```
sharedPtr<Object> ptr1 = make_shared<Object>();
      │ (owns object, count=1)
      │
sharedPtr<Object> ptr2 = ptr1;
      │ (co-owns, count=2)
      │
~ptr2;  // count=1
~ptr1;  // count=0 → delete object
```

### Circular Reference Problem

**Potential Issue:**
```cpp
struct Node {
    sharedPtr<Node> next;
};

auto a = make_shared<Node>();
auto b = make_shared<Node>();
a->next = b;  // count(b) = 2
b->next = a;  // count(a) = 2
// Both reference each other
// At end of scope: both have count=1 (leaked!)
```

**Solution:** [Describe if using weak_ptr or other solution]

## Usage Examples

```cpp
// Example usage patterns
sharedPtr<int> ptr1(new int(42));
sharedPtr<int> ptr2 = ptr1;  // shares ownership

// Automatic cleanup when both go out of scope
```

## Performance Characteristics

### Overhead
- **Per-pointer:** [Size in bytes]
- **Per-object:** [Control block size]
- **Copy operation:** [Cost]

### Comparison

| Aspect | sharedPtr | Raw Pointer | unique_ptr |
|--------|-----------|-------------|-----------|
| Ownership | Shared | None | Exclusive |
| Overhead | Higher | None | Low |
| Copy | Shared | Dangling | Error |

## Thread Safety

**Reference count thread safety:**
- [ ] Atomic operations ensure thread-safe counting
- [ ] Data access still requires external synchronization
- [ ] Multiple readers safe: ✅
- [ ] Multiple writers need locks: ⚠️

## Comparison with Standard Library

How does `sharedPtr` compare to `std::shared_ptr`?

| Aspect | Custom | std::shared_ptr |
|--------|--------|-----------------|
| Reference counting | | |
| Memory efficiency | | |
| Performance | | |
| Features | | |

## Known Limitations

- [ ] [Circular reference issues]
- [ ] [Memory overhead compared to raw pointers]
- [ ] [Not suitable for all use cases]

## Best Practices

1. Prefer `make_shared` for allocation
2. Use `reset()` to explicitly release ownership
3. Don't create cycles with shared ownership
4. Consider `weak_ptr` for breaking cycles
5. Don't rely on order of destruction

## Future Optimizations

- [ ] [Better memory layout]
- [ ] [Support for custom deleters]
- [ ] [Weak pointer implementation]

---

**Related:** See [Lock-Free Queue Design](./lockFreeQueue.md) for thread-safe data structures.
