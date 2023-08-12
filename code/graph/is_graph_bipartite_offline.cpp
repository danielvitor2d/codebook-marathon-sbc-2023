#include <bits/stdc++.h>
using namespace std;
namespace IsGraphBipartiteOffline {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  vector<int> g[MAXN], color(MAXN, -1);
  // Runs in O(V + E)
  bool is_bipartite(int u, int c = 1) {
    color[u] = c;
    for (int to : g[u]) {
      if (color[to] == -1 && !is_bipartite(to, 1 - c)) {
        return false;
      } else if (color[to] == c) {
        return false;
      }
    }
    return true;
  }
}