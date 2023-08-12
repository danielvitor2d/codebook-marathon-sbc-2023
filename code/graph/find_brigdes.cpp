#include <bits/stdc++.h>
using namespace std;
namespace FindBridges {
  typedef pair<int, int> Edge;
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n, timer = 0;
  vector<int> g[MAXN], tin(MAXN, 0), low(MAXN, 0);
  vector<Edge> bridges;
  bitset<MAXN> visited;
  void dfs(int u, int p = -1) {
    visited[u] = true;
    tin[u] = low[u] = ++timer;
    for (int to : g[u]) {
      if (to == p) {
        continue;
      }
      if (visited[to]) { // Back edge 
        low[u] = min(low[u], tin[to]);
      } else {
        dfs(to, u);
        low[u] = min(low[u], low[to]);
        if (low[to] > tin[u]) {
          bridges.emplace_back(u, to);
        }
      }
    }
  }
  // 0-indexed
  // Runs in O(V + E)
  void find_bridges() {
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        dfs(i);
      }
    }
  }
}