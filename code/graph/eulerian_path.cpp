#include <bits/stdc++.h>
using namespace std;
namespace BidirectionalEulerianPath {
  #define MAXN int(1e5)
  typedef pair<int, int> pii;
  int n, m;
  vector<pii> g[MAXN]; // MAXN is the largest possible number of nodes
  vector<int> path, stage(MAXN);
  vector<bool> used;

  template <bool directed = false>
  void add_edge(int u, int v) {
	  int idx {(int) used.size()};
    used.emplace_back();
	  g[u].emplace_back(v, idx);
	  if (!directed) {
	    g[v].emplace_back(u, idx);
	  }
  }

  // Runs in O(V + E)
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

  // e can be any value if is_cycle is true
  bool undirected_eulerian_path(int s, int e, bool is_cycle) {
	  int odd_c {};
	  for (int i {}; i < n; ++i) {
		  if (g[i].size() % 2 != 0) {
			  ++odd_c;
		  }
	  }
	  if ((is_cycle && odd_c != 0) || (!is_cycle && odd_c > 2)) {
		  return false;
	  } else if (!is_cycle && (g[s].size() % 2 == 0 || g[e].size() % 2 == 0)) {
	    return false;
	  }
	  dfs(s);
	  if ((int) path.size() != m + 1) {
		  return false;
	  }
	  reverse(path.begin(), path.end());
	  return true;
  }

  // e can be any value if is_cycle is true
  bool directed_eulerian_path(int s, int e, bool is_cycle) {
    vector<int> in_degree(n, 0), out_degree(n, 0);
    for (int i {}; i < n; ++i) {
      out_degree[i] = g[i].size();
      for (auto [to, _] : g[i]) {
        ++in_degree[to];
      }
    }
    int odd_c {};
    for (int i {}; i < n; ++i) {
      if (is_cycle && in_degree[i] != out_degree[i]) {
        return false;
      }
      if (!is_cycle && abs(in_degree[i] - out_degree[i]) > 1) {
        return false;
      }
      odd_c += abs(in_degree[i] - out_degree[i]) == 1;
    }
    if (!is_cycle && odd_c > 2) {
      return false;
    } else if (!is_cycle && (out_degree[s] - in_degree[s] != 1 || in_degree[e] - out_degree[e] != 1)) {
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
