# Data Structure Design Overview

This document provides a high-level overview of all data structures in this repository and their design approaches. For detailed information on each structure, refer to the individual design documents.

## Quick Comparison

| Structure | Type | Key Feature | Thread-Safe | Complexity |
|-----------|------|-------------|-------------|-----------|
| [Vector](./vector.md) | Dynamic Array | Dynamic resizing | No | O(1) amortized |
| [Unordered Map](./unordered_map.md) | Hash Table | Fast lookups | No | O(1) average |
| [Lock-Free Queue](./lockFreeQueue.md) | Queue | Lock-free operations | Yes | O(1) |
| [Shared Pointer](./sharedPtr.md) | Memory Management | Reference counting | Yes | O(1) |
| [Spin Lock](./spinLock.md) | Synchronization | Busy-waiting | Yes | N/A |
| [Stock Price Queue](./stockPriceQueue.md) | Specialized Queue | Price tracking | Depends | O(log n) |

## Design Documents

- **[Vector Design](./vector.md)** - Dynamic array implementation with growth strategy and memory management
- **[Unordered Map Design](./unordered_map.md)** - Hash table with collision resolution
- **[Lock-Free Queue Design](./lockFreeQueue.md)** - Concurrent queue using atomic operations
- **[Shared Pointer Design](./sharedPtr.md)** - Memory management with automatic cleanup
- **[Spin Lock Design](./spinLock.md)** - Synchronization primitive for resource protection
- **[Stock Price Queue Design](./stockPriceQueue.md)** - Specialized data structure for financial data

## Design Principles

This repository follows these principles across all data structures:

1. **Performance First** - Optimize for speed while maintaining correctness
2. **Memory Efficiency** - Minimize overhead and waste
3. **Thread Safety** - Use appropriate synchronization where needed
4. **Simplicity** - Keep implementations clean and understandable
5. **Testability** - Ensure all components can be thoroughly tested

## Performance Tiers

### Linear Time Operations (O(n))
- Vector: Insert/delete in middle
- Unordered Map: Rehashing on full table

### Logarithmic Operations (O(log n))
- Stock Price Queue: Priority-based operations

### Constant Time Operations (O(1))
- Vector: Access, push_back (amortized)
- Unordered Map: Insert, lookup, delete (average)
- Lock-Free Queue: Enqueue, dequeue
- Shared Pointer: Reference counting operations

## Thread Safety Matrix

| Structure | Read-Safe | Write-Safe | Note |
|-----------|-----------|-----------|------|
| Vector | ❌ | ❌ | Requires external synchronization |
| Unordered Map | ❌ | ❌ | Requires external synchronization |
| Lock-Free Queue | ✅ | ✅ | Lock-free concurrent access |
| Shared Pointer | ✅ | ⚠️ | Thread-safe counting, not data |
| Spin Lock | N/A | N/A | Synchronization primitive |
| Stock Price Queue | ⚠️ | ⚠️ | Depends on implementation |

---

For implementation details, usage examples, and performance benchmarks, see individual design documents.
