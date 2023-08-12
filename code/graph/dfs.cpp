#include <bits/stdc++.h>
using namespace std;
namespace DFS {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  vector<int> g[MAXN];
  bitset<MAXN> visited;
  // Runs in O(V + E)
  void dfs(int u) {
    visited[u] = true;
    for(int to : g[u]) {
      if (!visited[to]) {
        dfs(to);
      }
    }
  }
}