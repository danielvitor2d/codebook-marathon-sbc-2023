#include <bits/stdc++.h>
using namespace std;
namespace BFS {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  int n;
  vector<int> g[MAXN];
  bitset<MAXN> visited;
  // Runs in O(V + E)
  void bfs(int s) {
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int to : g[u]) {
        if (!visited[to]) {
          q.push(to);
          visited[to] = true;
        }
      }
    }
  }
}