#include <bits/stdc++.h>
using namespace std;
namespace FindArticularPoints {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n, timer = 0;
  vector<int> g[MAXN], tin(MAXN, 0), low(MAXN, 0);
  bitset<MAXN> visited, is_articulation_point;
  void dfs(int u, int p = -1) {
    visited[u] = true;
    tin[u] = low[u] = ++timer;
    int children = 0;
    for (int to : g[u]) {
      if (to == p) {
        continue;
      }
      if (visited[to]) { // Back edge
        low[u] = min(low[u], tin[to]);
      } else {
        dfs(to, u);
        low[u] = min(low[u], low[to]);
        if (low[to] >= tin[u] && p != -1) {
          is_articulation_point[u] = true;
        }
        ++children;
      }
    }
    if (p == -1 && children > 1) {
      is_articulation_point[u] = true;
    }
  }
  // 0-indexed
  // Runs in O(V + E)
  void find_articulation_points() {
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        dfs(i);
      }
    }
  }
}