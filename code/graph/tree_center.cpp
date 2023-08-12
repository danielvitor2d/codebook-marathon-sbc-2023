#include <bits/stdc++.h>
using namespace std;
namespace TreeCenter {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  typedef pair<int, int> pii;
  typedef tuple<int, int, int> tiii;
  vector<int> g[MAXN];
  int parent[MAXN];
  pii dfs(int u, int d = 0, int p = -1) {
    pii most_distant {u, d};
    parent[u] = p;
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
  tiii get_most_distants() {
    int x {dfs(0).first};
    auto [y, d] = dfs(x);
    return {x, y, d};
  }
  // 0-indexed because of the get_most_distants arbitrary vertex
  // Runs in O(V + E)
  vector<int> get_center() {
    auto [x, y, k] = get_most_distants();
    vector<int> path;
    for (; x != y; y = parent[y]) {
      path.push_back(y);
    }
    path.push_back(x);
    if (k % 2 == 0) {
      return {path[k / 2]};
    }
    return {path[k / 2], path[(k + 1) / 2]};
  }
}