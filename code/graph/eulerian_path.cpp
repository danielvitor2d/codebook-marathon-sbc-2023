#include <bits/stdc++.h>
using namespace std;
namespace BidirectionalEulerianPath {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  typedef pair<int, int> pii;
  int n, m;
  vector<pii> g[MAXN];
  vector<int> path, stage(MAXN);
  vector<bool> used;
  void add_edge(int u, int v) {
    int idx {(int) used.size()};
    used.emplace_back();
    g[u].emplace_back(v, idx);
    g[v].emplace_back(u, idx);
  }
  void dfs(int u) {
    stack<int> s;
    s.push(u);
    while (!s.empty()) {
      int curr {s.top()};
      if (stage[curr] < (int) g[curr].size()) {
        auto [to, idx] = g[curr][stage[curr]];
        ++stage[curr];
        if (!used[idx]) {
          used[idx] = true;
          s.push(to);
        }
      } else {
        path.push_back(curr);
        s.pop();
      }
    }
  }
  // 0-indexed
  // Runs in O(V + E)
  bool eulerian_path(int s, bool is_cycle) {
    int odd_c = 0;
    for (int i = 0; i < n; ++i) {
      if (g[i].size() % 2 != 0) {
        ++odd_c;
      }
    }
    // Eulerian cycle: all vertexes have an even degree
    // Eulerian path: exactly two vertexes have an even degree
    if ((is_cycle && odd_c != 0) || (!is_cycle && odd_c > 2)) {
      return false;
    }
    dfs(s);
    if ((int) path.size() != m + 1) {
      return false;
    }
    reverse(path.begin(), path.end());
    return true;
  }
}