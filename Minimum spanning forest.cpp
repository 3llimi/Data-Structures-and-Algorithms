//Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
 
using namespace std;
 
template<typename Key, typename Value>
class MyUnorderedMap {
private:
    vector<pair<Key, Value>>* buckets;
    size_t size;
    size_t capacity;
 
    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }
 
public:
    MyUnorderedMap(size_t capacity = 10) : size(0), capacity(capacity) {
        buckets = new vector<pair<Key, Value>>[capacity];
    }
 
    ~MyUnorderedMap() {
        delete[] buckets;
    }
 
    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        for (auto& entry : buckets[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        buckets[index].emplace_back(key, value);
        size++;
    }
 
    Value* find(const Key& key) {
        size_t index = hash(key);
        for (auto& entry : buckets[index]) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }
 
    size_t getSize() const {
        return size;
    }
};
 
class Edge {
public:
    int source, destination, weight;
 
    Edge(int source, int destination, int weight) : source(source), destination(destination), weight(weight) {}
 
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};
 
class UnionFind {
public:
    vector<int> parent, rank;
 
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
 
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }
 
    void union_sets(int x, int y) {
        int xRoot = find(x), yRoot = find(y);
 
        if (xRoot == yRoot) return;
 
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot] += 1;
        }
    }
};
 
class Graph {
private:
    int numVertices;
    vector<Edge> edges;
 
public:
    Graph(int numVertices) : numVertices(numVertices) {}
 
    void addEdge(int source, int destination, int weight) {
        edges.push_back(Edge(source, destination, weight));
    }
 
    void quickSortEdges(int left, int right) {
        if (left < right) {
            int pivotIndex = partition(left, right);
            quickSortEdges(left, pivotIndex - 1);
            quickSortEdges(pivotIndex + 1, right);
        }
    }
 
    int partition(int left, int right) {
        Edge pivot = edges[right];
        int i = left - 1;
 
        for (int j = left; j < right; j++) {
            if (edges[j] < pivot) {
                i++;
                swap(edges[i], edges[j]);
            }
        }
 
        swap(edges[i + 1], edges[right]);
        return i + 1;
    }
 
    void AhmedBahaEddineAlimi_MST() {
        if (edges.empty()) {
            cout << numVertices << endl;
            for (int i = 1; i <= numVertices; i++) {
                cout << "1 " << i << endl;
            }
            return;
        }
 
        quickSortEdges(0, edges.size() - 1);
 
        UnionFind uf(numVertices + 1);
 
        vector<Edge> result;
 
        for (Edge& edge : edges) {
            int x = uf.find(edge.source);
            int y = uf.find(edge.destination);
 
            if (x != y) {
                result.push_back(edge);
                uf.union_sets(x, y);
            }
        }
 
        MyUnorderedMap<int, vector<Edge>> forest(numVertices + 1);
 
        for (int i = 1; i <= numVertices; i++) {
            int root = uf.find(i);
            forest.insert(root, vector<Edge>());
        }
 
        for (Edge& edge : result) {
            forest.find(uf.find(edge.source))->push_back(edge);
        }
 
        cout << forest.getSize() << endl;
        for (int i = 1; i <= numVertices; i++) {
            if (forest.find(i) != nullptr) {
                vector<int> uniqueVertices;
                for (Edge& e : *forest.find(i)) {
                    if (find(uniqueVertices.begin(), uniqueVertices.end(), e.source) == uniqueVertices.end())
                        uniqueVertices.push_back(e.source);
                    if (find(uniqueVertices.begin(), uniqueVertices.end(), e.destination) == uniqueVertices.end())
                        uniqueVertices.push_back(e.destination);
                }
                uniqueVertices.push_back(i);
 
                cout << uniqueVertices.size()-1 << " " << i << endl;
                for (Edge& e : *forest.find(i)) {
                    cout << e.source << " " << e.destination << " " << e.weight << endl;
                }
            }
        }
    }
};
 
int main() {
    int N, M;
    cin >> N >> M;
 
    Graph graph(N);
 
    for (int i = 0; i < M; i++) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph.addEdge(source, destination, weight);
    }
 
    graph.AhmedBahaEddineAlimi_MST();
 
    return 0;
}