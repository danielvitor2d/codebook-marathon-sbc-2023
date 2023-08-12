#include <bits/stdc++.h>
using namespace std;
namespace Prim {
  #define MAXN int(1e5) // MAXN is the largest possible number of nodes
  #define INF INT_MAX // INF is an absurd weight
  typedef pair<int, int> pii;
  int n;
  vector<pii> g[MAXN];
  int weight[MAXN];
  bitset<MAXN> marked;
  // 0-indexed
  // Runs in O((V + E) log V)
  int prim() {
    for (int i = 0; i < n; ++i) {
      weight[i] = INF;
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    weight[0] = 0;
    pq.push({0, 0});
    int mst_cost = 0;
    while (!pq.empty()) {
      int curr = pq.top().second;
      pq.pop();
      if (marked[curr]) {
        continue;
      }
      marked[curr] = true;
      mst_cost += weight[curr];
      for (auto [w, to] : g[curr]) {
        if (w < weight[to]) {
          weight[to] = w;
          pq.push({weight[to], to});
        }
      }
    }
    return mst_cost;
  }
}