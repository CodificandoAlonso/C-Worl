# C Implementation Projects Roadmap

## Project Structure
```
c-project/
├── .clang-format
├── .clang-tidy
├── Makefile
├── include/
│   └── *.h
├── src/
│   └── *.c
├── tests/
│   └── *.c
└── build/
```

---

## Phase 1: Foundations (Weeks 1-3)

### 1.1 Dynamic Array
- Growable array with amortized O(1) append
- Generic via void* or macro-based type safety
- Learn: memory allocation patterns, realloc strategy

### 1.2 Linked List (Singly + Doubly)
- Insert, delete, reverse, detect cycles (Floyd's)
- Learn: pointer manipulation, sentinel nodes

### 1.3 Hash Table
- Open addressing (linear/quadratic probing)
- Separate chaining variant
- FNV-1a or djb2 hash function
- Learn: load factors, collision resolution, resizing

### 1.4 Binary Search Tree
- Insert, delete, search, traversals
- Learn: recursion vs iteration, tree rotations (prep for AVL)

---

## Phase 2: Searching & Sorting (Weeks 4-6)

### 2.1 Search Algorithms
- Binary search (iterative + recursive)
- Interpolation search
- Exponential search
- Learn: loop invariants, termination proofs

### 2.2 Comparison Sorts
- Quicksort (Hoare + Lomuto partition)
- Mergesort (top-down + bottom-up)
- Heapsort (implement heap first)
- Learn: divide-and-conquer, in-place vs stable

### 2.3 Non-Comparison Sorts
- Counting sort
- Radix sort (LSD + MSD)
- Bucket sort
- Learn: when O(n) is achievable

---

## Phase 3: Advanced Data Structures (Weeks 7-10)

### 3.1 AVL Tree
- Self-balancing with rotations
- Learn: balance factors, rotation cases

### 3.2 Red-Black Tree
- Alternative balancing strategy
- Learn: color properties, rebalancing rules

### 3.3 Priority Queue / Binary Heap
- Min-heap and max-heap
- Heapify, extract, decrease-key
- Learn: array-based tree representation

### 3.4 Trie (Prefix Tree)
- Insert, search, prefix matching
- Autocomplete implementation
- Learn: space-time tradeoffs

### 3.5 Bloom Filter
- Probabilistic set membership
- Multiple hash functions
- Learn: false positive rates, bit manipulation

---

## Phase 4: Graph Algorithms (Weeks 11-14)

### 4.1 Graph Representation
- Adjacency matrix
- Adjacency list
- Edge list
- Learn: density considerations

### 4.2 Traversals
- BFS (queue-based)
- DFS (stack-based + recursive)
- Topological sort
- Learn: visited tracking, cycle detection

### 4.3 Shortest Paths
- Dijkstra (with min-heap)
- Bellman-Ford (negative edges)
- Floyd-Warshall (all-pairs)
- A* (heuristic search)
- Learn: relaxation, negative cycles

### 4.4 Minimum Spanning Tree
- Prim's algorithm
- Kruskal's algorithm (needs Union-Find)
- Learn: greedy correctness proofs

### 4.5 Union-Find (Disjoint Set)
- Path compression
- Union by rank
- Learn: amortized analysis

---

## Phase 5: String Algorithms (Weeks 15-17)

### 5.1 Pattern Matching
- Naive O(nm)
- KMP (Knuth-Morris-Pratt)
- Rabin-Karp (rolling hash)
- Boyer-Moore
- Learn: failure functions, fingerprinting

### 5.2 Suffix Array
- Construction (naive, then DC3/SA-IS)
- LCP array
- Learn: string preprocessing

### 5.3 Longest Common Subsequence
- Dynamic programming approach
- Space optimization (Hirschberg)
- Learn: DP on strings

---

## Phase 6: Cryptography (Weeks 18-24)

### 6.1 Hashing
- SHA-256 (implement from spec)
- MD5 (educational, broken)
- HMAC construction
- Learn: Merkle-Damgård, padding

### 6.2 Symmetric Encryption
- AES-128 (implement from FIPS 197)
- Block cipher modes: ECB, CBC, CTR
- Learn: substitution-permutation networks, key schedule

### 6.3 Asymmetric Basics
- Big integer arithmetic (add, multiply, mod)
- Modular exponentiation (square-and-multiply)
- Extended Euclidean algorithm
- Miller-Rabin primality test
- Learn: number theory fundamentals

### 6.4 RSA
- Key generation
- Encrypt/decrypt
- PKCS#1 padding
- Learn: why padding matters, textbook RSA attacks

### 6.5 Diffie-Hellman
- Key exchange protocol
- Learn: discrete logarithm problem

### 6.6 Stream Ciphers (Bonus)
- ChaCha20
- Learn: ARX design

---

## Phase 7: Systems Programming Extras (Ongoing)

### 7.1 Memory Allocator
- First-fit, best-fit, buddy system
- Pool allocator
- Learn: fragmentation, alignment

### 7.2 Thread Pool
- Worker threads + job queue
- Learn: pthreads, synchronization primitives

### 7.3 Simple Regex Engine
- Thompson NFA construction
- Subset construction (NFA→DFA)
- Learn: automata theory applied

### 7.4 LZ77 Compression
- Sliding window
- Learn: dictionary-based compression

### 7.5 CRC-32
- Bitwise implementation
- Table-driven optimization
- Learn: polynomial division over GF(2)

---

## Testing Strategy

For each module:
1. Unit tests with assertions
2. Edge cases (empty, single element, max size)
3. Randomized testing where applicable
4. Memory leak checking with ASan

---

## Recommended Reading

- "The C Programming Language" (K&R)
- "Introduction to Algorithms" (CLRS) for algorithm theory
- "Applied Cryptography" (Schneier) for crypto context
- FIPS 180-4 (SHA), FIPS 197 (AES) for specs
- https://craftinginterpreters.com for parsing/VM if interested

---

## Notes

- Start each module with a header file defining the interface
- Write tests before implementation when possible
- Run `make check` before every commit
- Keep functions under 40 lines (enforced by clang-tidy)
- Document complexity in comments: // O(n log n) time, O(n) space
