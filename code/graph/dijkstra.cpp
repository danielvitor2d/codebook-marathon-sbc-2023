#include <bits/stdc++.h>
using namespace std;
namespace SparseDijkstra {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  #define INF 0xf3f3f3f3 // INF is a distance that can represent the node as unreachable
  typedef pair<int, int> pii;
  int n;
  int dist[MAXN];
  bitset<MAXN> marked;
  vector<pii> g[MAXN];
  // Runs in O((V + E) * lg V)
  void dijkstra(int s) {
      for (int i = 0; i < n; ++i) {
        dist[i] = INF;
      }
      priority_queue<pii, vector<pii>, greater<pii>> pq;
      dist[s] = 0;
      pq.push({0, s});
      while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();
        if (marked[curr]) {
          continue;
        }
        marked[curr] = true;
        for (auto [w, to] : g[curr]) {
          if (dist[curr] + w < dist[to]) {
            dist[to] = dist[curr] + w;
            pq.push({dist[to], to});
          }
        }
      }
  }
}
namespace DenseDijkstra {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  #define INF 0xf3f3f3f3 // INF is a distance that can represent the node as unreachable
  typedef pair<int, int> pii;
  int n;
  int dist[MAXN];
  bitset<MAXN> marked;
  vector<pii> g[MAXN];
  // 0-indexed
  // Runs in O(V^2 + E)
  void dijkstra(int s) {
      for (int i = 0; i < n; ++i) {
        dist[i] = INF;
      }
      dist[s] = 0;
      for (int i = 0; i < n; ++i) {
        int curr = -1;
        for (int j = 0; j < n; ++j) {
          if (marked[j]) {
            continue;
          }
          if (curr == -1 || dist[j] < dist[curr]) {
            curr = j;
          }
        }
        marked[curr] = true;
        for (auto [w, to] : g[curr]) {
          dist[to] = min(dist[to], dist[curr] + w);
        }
      }
  }
}