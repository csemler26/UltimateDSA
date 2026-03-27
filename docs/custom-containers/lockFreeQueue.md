# Lock-Free Queue Design Document

## Overview

The `lockFreeQueue` provides thread-safe concurrent access to queue operations without using traditional locks, using atomic operations instead.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. Lock-Free Fundamentals

```
Standard Queue (with lock):        Lock-Free Queue (atomic operations):
┌──────────┐                       ┌──────────┐
│  LOCK    │ ──→ critical section  │ atomics  │ ──→ no blocking
│  Queue   │                       │ Queue    │
└──────────┘                       └──────────┘
   Mutex-based                        CAS-based
```

### 2. Queue Node Structure

```cpp
// Typical node for lock-free queue
template<typename T>
struct Node {
    T data;
    std::atomic<Node*> next;  // Atomic pointer to next node
};

Head ────┐
         ▼
       [Node] ──→ [Node] ──→ [Node] ──→ NULL
         ▲                               
         Tail
```

### 3. Atomic Operations Used

**Document which atomic operations your implementation uses:**
- [ ] `compare_and_swap` (CAS) / `compare_exchange_strong`
- [ ] `load` / `store`
- [ ] Memory ordering (Relaxed, Release, Acquire, Seq_cst)

## Operations

### Concurrent Operations

| Operation | Time Complexity | Thread-Safe | Notes |
|-----------|-----------------|-------------|-------|
| `enqueue(val)` | O(1) | ✅ Yes | No locks needed |
| `dequeue()` | O(1) | ✅ Yes | No locks needed |
| `is_empty()` | O(1) | ✅ Yes | Lock-free check |

### Implementation Details

#### Enqueue Algorithm

```
1. Allocate new node
2. Set node.next = NULL
3. Loop:
   - old_tail = tail.load()
   - if tail.compare_exchange(old_tail, new_node):
       - success, break
   - else:
       - retry
4. Update head pointer
```

**Your implementation strategy:** [Describe]

#### Dequeue Algorithm

```
1. Loop:
   - old_head = head.load()
   - if old_head == NULL:
       - return empty
   - new_head = old_head.next
   - if head.compare_exchange(old_head, new_head):
       - success, break
   - else:
       - retry
2. Extract value from old_head
3. Free old_head
4. Return value
```

**Your implementation strategy:** [Describe]

## Memory Ordering

Explain the memory ordering guarantees:

- **Relaxed:** [When used]
- **Release:** [When used]
- **Acquire:** [When used]
- **Sequential Consistent:** [When used]

## ABA Problem & Solutions

**The ABA Problem:** A pointer value changes A→B→A between reads

```
Thread 1: Read ptr=A
Thread 2: Modifies, ptr becomes B
Thread 2: Further modifies, ptr becomes A again
Thread 1: CAS succeeds but state is different!
```

**How does your implementation handle this?**
- [ ] Tagged pointers / versioning
- [ ] Epoch-based reclamation
- [ ] Other: [Describe]

## Memory Reclamation

**How is memory freed safely?**

- [ ] Deferred deletion with epoch
- [ ] Hazard pointers
- [ ] Reference counting
- [ ] Manual verification

**Details:** [Describe your approach]

## Usage Examples

```cpp
// Example usage patterns
lockFreeQueue<int> queue;
queue.enqueue(42);
auto value = queue.dequeue();
```

## Performance Characteristics

### Throughput
- High concurrency: [Expected operations/second]
- Single-threaded: [Performance vs standard queue]

### Scalability
- How does performance scale with thread count?
- Any contention points?

## Comparison with Locking Approaches

| Aspect | Lock-Free | Lock-Based |
|--------|-----------|-----------|
| Throughput | | |
| Latency | | |
| Memory | | |
| Complexity | | |

## Known Limitations

- [ ] [Memory overhead]
- [ ] [Specific thread counts where it shines]
- [ ] [Worst-case behavior]

## Testing Considerations

- Stress testing with many threads
- ABA problem testing
- Memory leak detection
- Performance benchmarking

---

**Related:** See [Spin Lock Design](./spinLock.md) for a simpler synchronization primitive.
