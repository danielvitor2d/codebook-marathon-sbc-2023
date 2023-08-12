#include <bits/stdc++.h>
using namespace std;
namespace ConnectedComponents {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n;
  vector<int> g[MAXN], component(MAXN, -1);
  void dfs(int u, int c) {
    component[u] = c;
    for (int to : g[u]) {
      if (component[to] == -1) {
        dfs(to, c);
      }
    }
  }
  // 0-indexed
  // Runs in O(V + E)
  int cc() {
    int comp = 0;
    for (int i = 0; i < n; ++i) {
      if (component[i] == -1) {
        dfs(i, comp++);
      }
    }
    return comp;
  }
}