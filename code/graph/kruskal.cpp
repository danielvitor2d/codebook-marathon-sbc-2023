#include <bits/stdc++.h>
#include "../data_structures/union_find.hpp"
using namespace std;
namespace Kruskal {
  typedef tuple<int, int, int> Edge;
  int n;
  vector<Edge> edges;
  int kruskal() {
    sort(edges.begin(), edges.end());
    UnionFind::build(n);
    int mst_cost = 0;
    for (auto [u, v, w] : edges) {
      if (UnionFind::find(u) != UnionFind::find(v)) {
        UnionFind::join(u, v);
        mst_cost += w;
      }
    }
    return mst_cost;
  }
}