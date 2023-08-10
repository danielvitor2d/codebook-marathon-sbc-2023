#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
using namespace std;
using i64 = long long;
using tp = tuple<int, int, i64>; // (u, to, cap)
template<typename flow_t>
struct Dinitz {
  struct FlowEdge {
    int from, to, id;
    flow_t cap, flow = 0;
    FlowEdge(int f, int t, flow_t c, int id1) : from(f), to(t), cap(c) {
      id = id1;
    }
  };
  const flow_t flow_inf = numeric_limits<flow_t>::max();
  vector<FlowEdge> edges;
  vector<vector<int>> gr;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;
  bool bfs() {
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : gr[u]) {
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].to] != -1)
          continue;
        level[edges[id].to] = level[u] + 1;
        q.push(edges[id].to);
      }
    }
    return level[t] != -1;
  }
  flow_t dfs(int u, flow_t pushed) {
    if (pushed == 0)
      return 0;
    if (u == t)
      return pushed;
    for (int &cid = ptr[u]; cid < (int)gr[u].size(); ++cid) {
      int id = gr[u][cid];
      int to = edges[id].to;
      if (level[u] + 1 != level[to] or edges[id].cap - edges[id].flow < 1)
        continue;
      flow_t tr = dfs(to, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id^1].flow -= tr;
      return tr;
    }
    return 0;
  }
  Dinitz() {}
  void init(int _n) {
    n = _n;
    gr.assign(n, vector<int>());
    level.assign(n, 0);
    ptr.assign(n, 0);
  }
  void addEdge(int from, int to, flow_t cap, int id=0) {
    edges.emplace_back(from, to, cap, id);
    edges.emplace_back(to, from, 0, -id);
    gr[from].push_back(m);
    gr[to].push_back(m + 1);
    m += 2;
  }
  void resetFlow() {
    for (int i=0; i<m; ++i)
      edges[i].flow = 0;
  }
  flow_t maxFlow(int s1, int t1) {
    s = s1, t = t1;
    flow_t f = 0;
    while (true) {
      level.assign(n, -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      ptr.assign(n, 0);
      while (flow_t pushed = dfs(s, flow_inf))
        f += pushed;
    }
    return f;
  }
};
// Returns the minimum cut edge IDs
vector<int> recoverCut(Dinitz<int> &d) {
  vector<bool> seen(d.n, false);
  queue<int> q;
  q.push(d.s);
  seen[d.s] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int idx : d.gr[u]) {
      auto e = d.edges[idx];
      if (e.cap == e.flow)
        continue;
      if (!seen[e.to]) {
        q.push(e.to);
        seen[e.to] = true;
      }
    }
  }
  vector<int> ans;
  for (auto e : d.edges) {
    if (e.cap > 0 and (e.cap == e.flow) and (seen[e.from] != seen[e.to])) {
      if (e.id >= 0)
        ans.push_back(e.id);
    }
  }
  return ans;
}
//O(V*E*log(MAXC))
i64 maxFlowWithScaling(int n, vector<tp> edges, int s, int t) {
  Dinitz<i64> graph;
  graph.init(n);
  sort(all(edges), [&](tp a, tp b) {
    return get<2>(a) < get<2>(b);
  });
  i64 ans = 0;
  for(int l=(1 << 30); l > 0; l >>= 1) {
    while (!edges.empty()) {
      auto [u, to, cap] = edges.back();
      if (cap >= l) {
        graph.addEdge(u, to, cap);
        edges.pop_back();
      } else break;
    }
    ans += graph.maxFlow(s, t);
  }
  return ans;
}
int main() {

}