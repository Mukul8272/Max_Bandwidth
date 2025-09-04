# 📌 Widest Path Problem (Maximum Bottleneck Path)

This project implements the **Widest Path Problem** in C++ using a priority queue approach (modified Dijkstra’s algorithm).  
The goal is to find a path between two nodes such that the **minimum edge capacity** along the path is maximized.  

---

## 🔹 Problem Statement
Given an undirected weighted graph where edge weights represent capacities, find the path from **source (s)** to **target (t)** that has the **maximum possible minimum capacity**.  
This is also called the **Maximum Bottleneck Path** or **Widest Path Problem**.

---

## 🔹 Graph Example

For this input:

```cpp
int numNodes = 6;
vector<vector<int>> links = {
    {0, 1, 5},
    {0, 2, 2},
    {1, 3, 6},
    {2, 3, 8},
    {3, 4, 1},
    {4, 5, 9},
};
int source = 0;
int target = 5;
```

The graph looks like this:

```
         (5)
    0 -------- 1
    |          |
  (2)|        (6)
    |          |
    2 -------- 3
       (8)     |
               |
              (1)
               |
               4
               |
              (9)
               |
               5
```

---

## 🔹 Output

```
Maximum Capacity: 1
Path: 0 1 3 4 5
```

Explanation:  
- Path `0 → 1 → 3 → 4 → 5` has bottleneck capacity `min(5, 6, 1, 9) = 1`.  
- Path `0 → 2 → 3 → 4 → 5` has bottleneck capacity `min(2, 8, 1, 9) = 1`.  
- Hence, the maximum possible capacity is **1**.

---

## 🔹 Algorithm (Modified Dijkstra)

1. Build adjacency list for the graph.  
2. Use a **max-heap priority queue** to always expand the path with the **largest minimum capacity**.  
3. Keep track of:  
   - `maxCapacity[node]`: best bottleneck capacity found so far.  
   - `parent[node]`: used for path reconstruction.  
4. Stop when the target node is reached.  
5. Backtrack using `parent[]` to recover the path.  

---

## 🔹 Complexity
- **Time Complexity:** `O(E log V)` (similar to Dijkstra’s algorithm).  
- **Space Complexity:** `O(V + E)` for adjacency list and auxiliary arrays.  

---

## 🔹 How to Run
```bash
g++ widest_path.cpp -o widest_path
./widest_path
```

---

✨ This implementation can be extended to handle **multiple queries** efficiently using a **Maximum Spanning Tree + LCA** approach.
