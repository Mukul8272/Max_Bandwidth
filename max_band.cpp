#include<bits/stdc++.h>

using namespace std;

// Structure to represent an edge with a destination node and capacity
struct Edge {
    int to;
    int capacity;
};

// Structure for elements in the priority queue
struct Path {
    int from;
    int to;
    int capacity;

    // Custom comparator for max-heap
    bool operator<(const Path& other) const {
        return capacity < other.capacity; // max-heap based on capacity
    }
};

// Function to build the adjacency list for the undirected graph
vector<vector<Edge>> buildAdjacencyList(const vector<vector<int>>& links, int numNodes) {
    vector<vector<Edge>> adjList(numNodes);

    for (auto link : links) {
        int u = link[0];
        int v = link[1];
        int cap = link[2];

        adjList[u].push_back({v, cap});
        adjList[v].push_back({u, cap});
    }

    return adjList;
}

// Function to find the path from s to t with maximum minimum capacity (widest path problem)
pair<int, vector<int>> findMaxCapacityPath(int numNodes, const vector<vector<int>>& links, int source, int target) {
    vector<bool> visited(numNodes, false);
    vector<int> parent(numNodes, -1);
    vector<int> maxCapacity(numNodes, -1);
    priority_queue<Path> maxHeap;

    vector<vector<Edge>> adjList = buildAdjacencyList(links, numNodes);

    visited[source] = true;

    for (Edge edge : adjList[source]) {
        maxCapacity[edge.to] = edge.capacity;
        parent[edge.to] = source;
        maxHeap.push({source, edge.to, edge.capacity});
    }

    while (!maxHeap.empty()) {
        Path current = maxHeap.top();
        maxHeap.pop();

        int u = current.from;
        int v = current.to;
        int cap = current.capacity;

        if (visited[v]) continue;
        visited[v] = true;

        if (v == target) break;

        for (Edge edge : adjList[v]) {
            if (!visited[edge.to]) {
                int newCap = min(maxCapacity[v], edge.capacity);
                if (newCap > maxCapacity[edge.to]) {
                    maxCapacity[edge.to] = newCap;
                    parent[edge.to] = v;
                    maxHeap.push({v, edge.to, newCap});
                }
            }
        }
    }

    // Build the route by backtracking from the target
    vector<int> route;
    int node = target;
    if (maxCapacity[node] == -1) return {-1, route}; // no path found

    while (node != -1) {
        route.push_back(node);
        node = parent[node];
    }
    reverse(route.begin(), route.end());

    return {maxCapacity[target], route};
}

// Example usage
int main() {
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

    auto result = findMaxCapacityPath(numNodes, links, source, target);
    int capacity = result.first;
    vector<int> path = result.second;

    cout << "Maximum Capacity: " << capacity << endl;
    cout << "Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
