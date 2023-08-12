#include <bits/stdc++.h>
using namespace std;
namespace UnionFind {
  #define MAXN int(1e5) // MAXN is the largest possible number of elements
  int p[MAXN];
  int h[MAXN];
  // Runs in O(1) amortized
  int find(int x) {
    if (p[x] == x) {
      return x;
    }
    return p[x] = find(p[x]);
  }
  // Runs in O(1) amortized
  void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (h[x] < h[y]) {
      swap(x, y);
    }
    p[y] = x;
    if (h[x] == h[y]) {
      ++h[x];
    }
  }
  // 0-indexed
  // Build: O(n)
  void build(int n) {
    for (int i = 0; i < n; ++i) {
      p[i] = i;
    }
  }
}
namespace UnionFindWithRollback {
  #define MAXN int(1e5) // MAXN is the largest possible number of elements
  int p[MAXN];
  int h[MAXN];
  vector<tuple<int, int, int, int>> op;
  // Runs in O(log n)
  int find(int x) {
    if (p[x] == x) {
      return x;
    }
    return find(p[x]);
  }
  // Runs in O(log n)
  void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (h[x] < h[y]) {
      swap(x, y);
    }
    op.emplace_back(x, h[x], y, p[y]);
    p[y] = x;
    if (h[x] == h[y]) {
      ++h[x];
    }
  }
  // Runs in O(t)
  void rollback(int t) {
    while ((int) op.size() > t) {
      auto [x, hx, y, py] = op.back();
      h[x] = hx;
      p[y] = py;
      op.pop_back();
    }	
  }
  // Runs in O(1)
  int time() {
    return (int) op.size();
  }
}