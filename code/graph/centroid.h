#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int L = 19;
int n, m;
vector<vector<int>> gr;
vector<int> sub, dad;
vector<bool> removed;
int timer;
vector<vector<int>> up;
vector<int> in, out, h;
vector<int> clr;
vector<multiset<int>> ans;
int dfs(int u, int par) {
  sub[u] = 1;
  for (int to : gr[u]) if (to != par and !removed[to]) {
    sub[u] += dfs(to, u);
  }
  return sub[u];
}
int getCentroid(int u, int par, int sz) {
  for (int to : gr[u]) if (to != par) {
    if (!removed[to] and 2 * sub[to] > sz) return getCentroid(to, u, sz);
  }
  return u;
}
int decomp(int u, int par) {
  int sz = dfs(u, par);
  int centroid = getCentroid(u, par, sz);
  if (par == -1)
    par = centroid;
  removed[centroid] = true;
  dad[centroid] = par;
  for (int to : gr[centroid]) if (!removed[to]) {
    decomp(to, centroid);
  }
  return centroid;
}
void dfs_lca(int u, int d, int par = -1) {
  in[u] = ++timer;
  h[u] = d;
  up[u][0] = par;
  for (int to : gr[u]) if (to != par) {
    dfs_lca(to, d+1, u);
  }
  out[u] = ++timer;
}
bool is_anc(int a, int b) {
  return in[a] <= in[b] and out[b] <= out[a];
}
int lca(int a, int b) {
  if (is_anc(a, b)) return a;
  if (is_anc(b, a)) return b;
  for (int k = L-1; k >= 0; --k) {
    if (up[a][k] != -1 and !is_anc(up[a][k], b)) {
      a = up[a][k];
    }
  }
  return up[a][0];
}
void calc_up() {
  for (int k = 1; k < L; ++k) {
    for (int u = 0; u < n; ++u) {
      if (up[u][k-1] != -1) {
        up[u][k] = up[ up[u][k-1] ][k-1];
      }
    }
  }
}
int dist(int a, int b) {
  return h[a] + h[b] - 2 * h[lca(a, b)];
}
void paint(int o) {
  int u = o;
  clr[o] ^= 1;
  if (!clr[o]) {
    // virou branco
    while (true) {
      ans[u].insert(dist(u, o));
      if (u == dad[u]) break;
      u = dad[u];
    }
  } else {
    // virou preto
    while (true) {
      ans[u].erase(ans[u].find(dist(u, o)));
      if (u == dad[u]) break;
      u = dad[u];
    }
  }
}
int getAns(int o) {
  int answer = INF;
  int u = o;
  while(true) {
    if (!ans[u].empty())
      answer = min(answer, (*ans[u].begin()) + dist(u, o));
    if (u == dad[u]) break;
    u = dad[u];
  }
  return answer == INF ? -1 : answer;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  gr.assign(n, vector<int>());
  sub.assign(n, 0);
  dad.assign(n, 0);
  removed.assign(n, false);
  up.assign(n, vector<int>(L, -1));
  h.assign(n, 0);
  in.assign(n, 0);
  out.assign(n, 0);
  ans.assign(n, multiset<int>());
  clr.assign(n, 1);
  for (int i = 0; i < n-1; ++i) {
    int a, b; cin >> a >> b, --a, --b;
    gr[a].push_back(b);
    gr[b].push_back(a);
  }
  dfs_lca(0, 0, -1);
  calc_up();
  decomp(0, -1);
  cin >> m;
  while (m--) {
    int t, v; cin >> t >> v, --v;
    if (t == 0) {
      paint(v);
    } else {
      cout << getAns(v) << '\n';
    }
  }
} 