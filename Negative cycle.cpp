//Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 1000000;
 
class Edge {
public:
    int destination;
    int weight;
    Edge(int dest, int w) : destination(dest), weight(w) {}
};
 
class Vertex {
public:
    int data;
    list<Edge> edges;
    Vertex(int d) : data(d) {}
};
 
class Graph {
private:
    int numVertices;
    vector<Vertex> vertices;
 
public:
    Graph(int numVertices) : numVertices(numVertices) {
        vertices.resize(numVertices, Vertex(-1));
    }
 
    void addEdge(int source, int destination, int weight) {
        vertices[source].edges.emplace_back(destination, weight);
    }
 
    bool AhmedBahaEddineAlimi_sp() {
        vector<int> distance(numVertices, 100000);
        vector<int> predecessor(numVertices, -1);
        int start = -1;
 
        distance[0] = 0;
 
        for (int i = 0; i < numVertices; ++i) {
            start = -1;
            for (int from = 0; from < numVertices; ++from) {
                for (const auto& edge : vertices[from].edges) {
                    int to = edge.destination;
                    if (distance[from] < INF && distance[to] > distance[from] + edge.weight) {
                        distance[to] = distance[from] + edge.weight;
                        predecessor[to] = from;
                        start = to;
                    }
                }
            }
        }
 
        if (start == -1) return false;
 
        for (int i = 0; i < numVertices; ++i) {
            start = predecessor[start];
        }
 
        vector<int> cycle;
        int cur = start;
        do {
            cycle.push_back(cur + 1);
            cur = predecessor[cur];
        } while (cur != start);
 
        reverse(cycle.begin(), cycle.end());
 
        cout << "YES" << endl;
        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
 
        return true;
    }
};
 
int main() {
    int N;
    cin >> N;
 
    Graph graph(N);
 
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int weight;
            cin >> weight;
            if (weight != 100000) {
                graph.addEdge(i, j, weight);
            }
        }
    }
 
    if (!graph.AhmedBahaEddineAlimi_sp()) {
        cout << "NO" << endl;
    }
 
    return 0;
}