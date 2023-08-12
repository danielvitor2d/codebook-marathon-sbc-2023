#include <bits/stdc++.h>
using namespace std;
namespace BidirectionalFindCycle {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n;
  vector<int> g[MAXN], parent(MAXN, -1);
  bitset<MAXN> visited;
  int cycle_start = -1, cycle_end;
  bool dfs(int u, int p = -1) {
    visited[u] = true;
    for (int to : g[u]) {
      if (to == p) {
        continue;
      }
      if (visited[to]) {
        cycle_end = u;
        cycle_start = to;
        return true;
      }
      parent[to] = u;
      if (dfs(to, parent[to])) {
        return true;
      }
    }
    return false;
  }
  // 0-indexed
  // Runs in O(V + E)
  vector<int> find_cycle() {
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && dfs(i)) {
        break;
      }
    }
    if (cycle_start == -1) {
      return {};
    }
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int v = cycle_end; v != cycle_start; v = parent[v]) {
      cycle.push_back(v);
    }
    cycle.push_back(cycle_start);
    return cycle;
  }
}
namespace DirectionalFindCycle {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n;
  vector<int> g[MAXN], parent(MAXN, -1);
  vector<char> color(MAXN, 0);
  int cycle_start = -1, cycle_end;
  bool dfs(int u) {
    color[u] = 1;
    for (int to : g[u]) {
      if (color[to] == 0) {
        parent[to] = u;
        if (dfs(to)) {
          return true;
        }
      } else if (color[to] == 1) {
        cycle_end = u;
        cycle_start = to;
        return true;
      }
    }
    color[u] = 2;
    return false;
  }
  // 0-indexed
  // Runs in O(V + E)
  vector<int> find_cycle() {
    for (int i = 0; i < n; ++i) {
      if (color[i] == 0 && dfs(i)) {
        break;
      }
    }
    if (cycle_start == -1) {
      return {};
    }
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int v {cycle_end}; v != cycle_start; v = parent[v]) {
      cycle.push_back(v);
    }
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());
    return cycle;
  }
}