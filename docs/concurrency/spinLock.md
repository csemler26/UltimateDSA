# Spin Lock Design Document

## Overview

The `spinLock` is a simple synchronization primitive that uses busy-waiting (spinning) instead of blocking to acquire a lock.

**Back to [Design Overview](./DESIGN_OVERVIEW.md)**

## Core Concepts

### 1. How Spin Locks Work

```
Thread A wants lock:
┌─────────┐
│ SPIN    │  ← Keep checking if lock is free
│ SPIN    │     while (locked) { /* retry */ }
│ SPIN    │
│ LOCKED! │  ← Successfully acquired
└─────────┘

vs. Mutex:
┌──────────┐
│ BLOCKED  │  ← Put thread to sleep
│ BLOCKED  │     (awakened when lock released)
│ BLOCKED  │
│ RUNNING! │
└──────────┘
```

### 2. Lock State

```
┌──────────────┐
│ Spin Lock    │
├──────────────┤
│ locked flag  │
│ (atomic)     │
│ 0 = free     │
│ 1 = locked   │
└──────────────┘
```

## Operations

### Core Operations

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `lock()` | O(1) average | Busy-wait loop |
| `unlock()` | O(1) | Simple store |
| `try_lock()` | O(1) | Non-blocking attempt |

### Implementation Pattern

```cpp
class spinLock {
    std::atomic<bool> locked{false};
    
    void lock() {
        // Spin until we can acquire
        while (locked.exchange(true, std::memory_order_acquire)) {
            // Keep trying
        }
    }
    
    void unlock() {
        locked.store(false, std::memory_order_release);
    }
};
```

**Your implementation:** [Document any optimizations]

## Memory Ordering

**Atomic operations and memory ordering:**

- **lock():** `memory_order_acquire`
  - Prevents later operations from reordering before
  - Ensures we see all changes made before unlock
  
- **unlock():** `memory_order_release`
  - Prevents earlier operations from reordering after
  - Ensures others see all our changes

```
Thread 1                    Thread 2
lock() ────┐               
shared_var │ ──────→ unlock()
unlock()   │               lock()
           └────────→ read shared_var
```

## Performance Characteristics

### When Spin Locks Excel
✅ Very short critical sections
✅ Single-core/few threads
✅ Predictable latency needed
✅ Rare contention

### When Spin Locks Struggle
❌ Long critical sections
❌ Many threads competing
❌ Wasted CPU cycles
❌ Power-sensitive systems

### Comparison

| Metric | Spin Lock | Mutex |
|--------|-----------|-------|
| Latency | Very low (~1μs) | Higher (~100μs) |
| CPU Usage | High (spinning) | Low (blocked) |
| Fairness | Fair | Fair |
| Scalability | Poor | Better |

## Contention Analysis

```
Light contention:      Heavy contention:
[lock acquired]        [severe contention]
[work quickly]    vs   [all CPUs spinning]
[unlock]                [wasted CPU]
→ Spin lock wins        → Mutex wins
```

## Cache Coherency Implications

```
Core 1              Core 2
lock = 1            while (lock == 1) {
┌────┐                  /* spin */
│    │ ──shared────→ ┌────┐
│    │   cache       │    │
│    │ ←─coherent─ │    │
└────┘              └────┘
```

## Usage Examples

```cpp
// Protecting critical section
spinLock lock;

{
    std::lock_guard<spinLock> guard(lock);
    // Critical section
    // Automatically unlocked when guard destroyed
}
```

## Variations & Optimizations

### 1. Backoff Strategies
- **Linear Backoff:** Add small delay between retries
- **Exponential Backoff:** Increase delay exponentially
- **Random Backoff:** Reduce thundering herd

**Your approach:** [Describe]

### 2. Pause Instructions
```cpp
// Some implementations use CPU pause hints
while (locked.exchange(true, memory_order_acquire)) {
    #ifdef __x86_64__
    _mm_pause();  // Hint to CPU: we're spinning
    #endif
}
```

**Included in your implementation?** [Yes/No]

## Known Limitations

- [ ] Wastes CPU cycles while spinning
- [ ] Poor scalability with many threads
- [ ] Not ideal for long-held locks
- [ ] Can't be used in interrupt handlers safely
- [ ] Potential for livelock in some scenarios

## Best Practices

1. **Only use for:** Very short critical sections (< 100 cycles)
2. **Avoid for:** I/O operations, blocking calls
3. **Monitor:** CPU usage in production
4. **Consider:** Hybrid approach (spin then block)
5. **Profile:** Measure actual contention

## Comparison with Standard Library

How does `spinLock` compare to `std::mutex`?

| Aspect | spinLock | std::mutex |
|--------|----------|-----------|
| Latency | Low | Higher |
| Scalability | Poor | Good |
| CPU Usage | High | Low |
| Predictability | Good | Variable |

## Future Optimizations

- [ ] Implement backoff strategy
- [ ] Add `try_lock()` timeout support
- [ ] CPU pause hint optimization
- [ ] Adaptive spin vs block

---

**Related:** See [Lock-Free Queue Design](./lockFreeQueue.md) for lock-free alternatives.
