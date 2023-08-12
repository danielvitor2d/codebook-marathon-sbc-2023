#include <bits/stdc++.h>
using namespace std;
namespace TreeDiameter {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  typedef pair<int, int> pii;
  vector<int> g[MAXN];
  pii dfs(int u, int d = 0, int p = -1) {
    pii most_distant {u, d};
    for (int to : g[u]) {
      if (to != p) {
        pii result {dfs(to, d + 1, u)};
        if (result.second > most_distant.second) {
          most_distant = result;
        }
      }
    }
    return most_distant;
  }
  // 0-indexed
  // Runs in O(V + E)
  int tree_diameter() {
    return dfs(dfs(0).first).second;
  }
}