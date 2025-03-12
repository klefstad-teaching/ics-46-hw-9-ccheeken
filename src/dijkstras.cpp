#include "dijkstras.h"

struct comparer {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distance(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    previous = vector<int>(G.numVertices, -1);  // make all previous 1
    priority_queue<pair<int, int>, vector<pair<int,int>>, comparer> pq;
    pq.push({source, 0});
    distance[source] = 0;
    while (!pq.empty()) {
        pair<int,int> current = pq.top();  // pair = (node, weight)
        pq.pop();
        int u = current.first;
        if (visited[u]) { continue; }
        visited[u] = true;
        for (auto & neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && (distance[u] + weight < distance[v])) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({v, distance[v]});
            }
        }
    } return distance;
}

// vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
//     // kms
// }

// void print_path(const vector<int>& v, int total) {
//     // kms
// }
