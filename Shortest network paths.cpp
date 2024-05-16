//Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
 
using namespace std;
 
template <typename T>
struct Vertex {
    int index;
    T data;
};
 
template <typename V, typename E>
class WeightedGraph {
private:
    int graphSize;
    int nbEdges;
    vector<vector<pair<E, int>>> adjacencyMatrix;
    vector<pair<pair<V, V>, int>> bandwidth;
    vector<Vertex<V>> nodes;
    E INIT;
public:
    WeightedGraph(E initial) {
        graphSize = 0;
        nbEdges = 0;
        this->INIT = initial;
    }
 
    void setAdjacencyMatrixSize(int n) {
        adjacencyMatrix.assign(n + 1, vector<pair<E, int>>(n + 1, make_pair(-1, -1)));
    }
 
    void addNode(V node) {
        graphSize++;
        Vertex<V> temp;
        temp.index = graphSize;
        temp.data = node;
        nodes.push_back(temp);
    }
 
    void addEdge(V a, V b, E weight, int band) {
        int va_index = -1, vb_index = -1;
        for (auto node : nodes) {
            if (node.data == a)
                va_index = node.index;
            if (node.data == b)
                vb_index = node.index;
        }
        if (va_index != -1 && vb_index != -1) {
            adjacencyMatrix[va_index][vb_index] = make_pair(weight, band);
            bandwidth.push_back(make_pair(make_pair(a, b), band));
            nbEdges++;
        }
    }
 
    void AhmedBahaEddine_sp(V start, V end, int minBandwidth) {
        vector<bool> visited(adjacencyMatrix.size(), false);
        vector<pair<E, int>> dist(adjacencyMatrix.size(), make_pair(numeric_limits<E>::max(), -1));
        vector<V> parent(adjacencyMatrix.size(), -1);
 
        dist[start] = make_pair(0, numeric_limits<int>::max());
 
        for (int i = 1; i <= graphSize; ++i) {
            V u = -1;
            for (int j = 1; j <= graphSize; ++j) {
                if (!visited[j] && (u == -1 || dist[j].first < dist[u].first))
                    u = j;
            }
 
            if (dist[u].first == numeric_limits<E>::max())
                break;
 
            visited[u] = true;
 
            for (int v = 1; v <= graphSize; ++v) {
                if (adjacencyMatrix[u][v].first != -1) {
                    E len = adjacencyMatrix[u][v].first;
                    int band = adjacencyMatrix[u][v].second;
 
                    if (dist[u].second != -1)
                        band = min(band, dist[u].second);
 
                    if (band < minBandwidth)
                        continue;
 
                    if (dist[v].second != -1) {
                        if (dist[v].second < minBandwidth)
                            continue;
                    }
 
                    if (dist[u].first + len < dist[v].first) {
                        dist[v].first = dist[u].first + len;
                        dist[v].second = band;
                        parent[v] = u;
                    }
                }
            }
        }
 
        if (dist[end].first == numeric_limits<E>::max()) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
 
        vector<V> path;
        path.push_back(end);
        V current = parent[end];
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
 
        reverse(path.begin(), path.end());
 
        int bandwidthResult = numeric_limits<int>::max();
        for (size_t i = 0; i < path.size() - 1; i++) {
            for (auto elt : bandwidth) {
                if (elt.first.first == path[i] && elt.first.second == path[i + 1]) {
                    bandwidthResult = min(bandwidthResult, elt.second);
                    break;
                }
            }
        }
 
        cout << path.size() << ' ' << dist[end].first << ' ' << bandwidthResult << endl;
        for (auto elt : path)
            cout << elt << ' ';
        cout << endl;
    }
};
 
int main() {
    int numberOfNodes, numberOfEdges;
    cin >> numberOfNodes >> numberOfEdges;
 
    WeightedGraph<int, int> graph(numeric_limits<int>::max());
    graph.setAdjacencyMatrixSize(numberOfNodes);
 
    for (int i = 1; i <= numberOfNodes; i++) {
        graph.addNode(i);
    }
 
    for (int i = 0; i < numberOfEdges; i++) {
        int nodeA, nodeB, length, bandwidth;
        cin >> nodeA >> nodeB >> length >> bandwidth;
        graph.addEdge(nodeA, nodeB, length, bandwidth);
    }
 
    int startNode, endNode, minimumBandwidth;
    cin >> startNode >> endNode >> minimumBandwidth;
 
    graph.AhmedBahaEddine_sp(startNode, endNode, minimumBandwidth);
 
    return 0;
}