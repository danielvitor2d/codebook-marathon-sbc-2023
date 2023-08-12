#include <bits/stdc++.h>
using namespace std;
namespace TopologicalSort {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n;
  int in_degree[MAXN];
  vector<int> g[MAXN];
  // 0-indexed
  // Runs in O(V + E)
  vector<int> topological_sort() {
    for (int i = 0; i < n; ++i) {
      for (int to : g[i]) {
        ++in_degree[to];
      }
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (in_degree[i] == 0) {
        q.push(i);
      }
    }
    vector<int> ans;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      ans.push_back(curr);
      for (int to : g[curr]) {
        if (--in_degree[to] == 0) {
          q.push(to);
        }
      }
    }
    if (ans.size() != n) {
      throw runtime_error("No topological sort");
    }
    return ans;
  }
}