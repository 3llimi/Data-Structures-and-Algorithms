#include<bits/stdc++.h>
 
using namespace std;
 
// Forward declaration for edge
template<class T, class W> struct edge;
 
// Generic struct of a node
template<class T>
struct node {
    T value;
    node<T>* prev;
    node<T>* next;
    edge<T, int>* head;
};
 
// Generic struct of an edge
template<class T, class W>
struct edge {
    // The weight of the edge
    W weight;
    // end-nodes of the edge
    node<T>* start;
    node<T>* end;
    edge<T, W>* prev;
    edge<T, W>* next;
};
 
// Generic struct of a graph
template<class T>
struct Graph {
    int n;
 
    // Vertex List
    vector<node<T>*> vertices;
 
    // Constructor
    Graph(int m) {
        n = m;
    }
 
    // Add a new node to the graph
    node<T>* addNode(T val) {
        node<T>* newNode = new node<T>;
        newNode->value = val;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        newNode->head = nullptr;
        vertices.push_back(newNode);
        return newNode;
    }
 
    // Add a new edge to the graph
    void addEdge(node<T>* u, node<T>* v, int weight) {
        edge<T, int>* newEdge = new edge<T, int>;
        newEdge->start = u;
        newEdge->end = v;
        newEdge->weight = weight;
        newEdge->prev = nullptr;
        newEdge->next = u->head;
        if (u->head != nullptr)
            u->head->prev = newEdge;
        u->head = newEdge;
    }
 
    // DFS traversal to check connectivity
    bool AhmedBahaEddineAlimi_dfs(node<T>* start, vector<bool>& visited) {
        if (start == nullptr)
            return false;
        visited[start->value] = true;
        edge<T, int>* currEdge = start->head;
        while (currEdge != nullptr) {
            node<T>* neighbor = currEdge->end;
            if (!visited[neighbor->value])
                AhmedBahaEddineAlimi_dfs(neighbor, visited);
            currEdge = currEdge->next;
        }
        return true;
    }
 
    // Check the connectivity. Worst case time complexity: O(V + E)
    string isConnected() {
        // Keep track of the visited nodes
        vector<bool> visited(n, false);
 
        // Start DFS from the first node
        if (!AhmedBahaEddineAlimi_dfs(vertices[0], visited))
            return "NO";
 
        // Check if all nodes are visited
        for (int i = 0; i < n; i++) {
            if (!visited[i])
                return "NO";
        }
        return "YES";
    }
};
 
int main() {
    int n;
    cin >> n;
    Graph<int> myGraph(n);
 
    // Add nodes to the graph
    for (int i = 0; i < n; i++) {
        myGraph.addNode(i);
    }
 
    // Get the adjacency matrix and add edges accordingly
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int weight;
            cin >> weight;
            if (weight == 1)
                myGraph.addEdge(myGraph.vertices[i], myGraph.vertices[j], weight);
        }
    }
 
    // Check the connectivity
    cout << myGraph.isConnected() << endl;
    return 0;
}