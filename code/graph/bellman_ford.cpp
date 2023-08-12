#include <bits/stdc++.h>
using namespace std;
namespace BellmanFord {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  #define INF 0x3f3f3f3f // INF is a distance that can represent the node as unreachable
  typedef tuple<int, int, int> Edge;
  int n, dist[MAXN];
  vector<Edge> edges;
  // 0-indexed
  // Runs in O(VE)
  void bellman_ford(int s) {
    for (int i = 0; i < n; ++i) {
      dist[i] = INF;
    }
    dist[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
      for (auto [u, v, w] : edges) {
        if (dist[u] != INF) {
          dist[v] = min(dist[v], dist[u] + w);
        }
      }
    }
    for (auto [u, v, w] : edges) {
      if (dist[u] + w < dist[v]) {
        throw runtime_error("Has negative cycle");
      }
    }
  }
}