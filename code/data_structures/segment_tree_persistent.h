#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> a;

struct Vertex {
  Vertex *l, *r;
  int sum;

  Vertex(int val): l(nullptr), r(nullptr), sum(val) {}
  Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
    if (l) sum += l->sum;
    if (r) sum += r->sum;
  }
};

Vertex* build(int l, int r) {
  if (l == r)
    return new Vertex(0);
  int m = l + (r - l) / 2;
  return new Vertex(
    build(l, m),
    build(m+1, r)
  ); 
}

int get_sum(Vertex* v, int l, int r, int ql, int qr) {
  if (l > r) return 0;
  if (l == ql and qr == r) return v->sum;
  int m = l + (r - l) / 2;
  return get_sum(v->l, l, m, ql, min(qr, m)) +
    get_sum(v->r, m+1, r, max(ql, m+1), qr);
}

Vertex* update(Vertex* v, int l, int r, int pos) {
  if (l == r) return new Vertex(v->sum + 1);
  int m = l + (r - l) / 2;
  if (pos <= m) return new Vertex(update(v->l, l, m, pos), v->r);
  else return new Vertex(v->l, update(v->r, m+1, r, pos));
}

int find_kth(Vertex* vl, Vertex* vr, int l, int r, int k) {
  if (l == r) return l;
  int m = l + (r - l) / 2;
  int cntLeft = vr->l->sum - vl->l->sum;
  if (cntLeft >= k)
    return find_kth(vl->l, vr->l, l, m, k);
  return find_kth(vl->r, vr->r, m+1, r, k-cntLeft);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> m;
  a.assign(n+1, 0);

  vector<int> C;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    C.push_back(a[i]);
  }

  sort(C.begin(), C.end());
  C.erase(unique(C.begin(), C.end()), C.end());

  map<int, int> mp;
  for (int i = 1; i <= n; ++i) {
    int x = (lower_bound(C.begin(), C.end(), a[i]) - C.begin()) + 1;
    mp[x] = a[i];
    a[i] = x;
  }

  int L = 1, R = C.size() + 1;

  vector<Vertex*> roots;
  roots.push_back(build(L, R));

  for (int i = 1; i <= n; ++i) {
    roots.push_back(update(roots.back(), L, R, a[i]));
  }

  while (m--) {
    int i, j, k; cin >> i >> j >> k;

    int pos = find_kth(roots[i-1], roots[j], L, R, k);

    cout << mp[pos] << '\n';
  }
}