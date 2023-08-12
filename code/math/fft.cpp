#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ii = pair<int, int>;
using ll = pair<i64, i64>;
struct complex_t {
  double a = 0.0, b = 0.0;
  complex_t() {}
  complex_t(double na): a(na) {}
  complex_t(double na, double nb): a(na), b(nb) {}
  const complex_t operator+(const complex_t &c) const {
    return complex_t(a + c.a, b + c.b);
  }
  const complex_t operator-(const complex_t &c) const {
    return complex_t(a - c.a, b - c.b);
  }
  const complex_t operator*(const complex_t &c) const {
    return complex_t(a*c.a - b*c.b, a*c.b + b*c.a);
  }
  const complex_t operator/(const int &c) const {
    return complex_t(a/c, b/c);
  }
};
using cd = complex_t;
const double PI = acos(-1.0);
void fft(vector<cd> & a, bool invert) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1)
      j ^= bit;
    j ^= bit;
    if (i < j)
      swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v;
        a[i+j+len/2] = u - v;
        w = w * wlen;
      }
    }
  }
  if (invert) {
    for (cd & x : a){
      x = x / n;
    }
  }
}
vector<i64> multiply(const vector<int>& a, const vector<int>& b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while(n < int(a.size() + b.size()))
    n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] = fa[i]*fb[i];
  fft(fa, true);
  vector<i64> result(n);
  for (int i = 0; i < n; i++)
    result[i] = round(fa[i].a);
  return result;
}
vector<i64> scalarProduct(vector<int> t, vector<int> p, bool isCyclic=false) {
  int nt = t.size();
  int np = p.size();
  t.resize(nt+np);
  reverse(p.begin(), p.end());
  if (isCyclic)
    for (int i=nt; i<nt+np; ++i)
      t[i] = t[i%nt];
  vector<i64> ans = multiply(t, p);
  for (int i = 0; i < nt; ++i) // nt-np+1 if compare with substring
    ans[i] = ans[np-1+i];
  ans.resize(nt);
  return ans;
}
inline int getID(char c){
  return c - 'a';
}
// Find p in text t. Wildcard character *
vector<bool> stringMatchingWithWildcards(string t, string p){
  int nt = t.size();
  int np = p.size();
  vector<cd> fa(nt), fb(np);
  for (int i=0; i<nt; ++i) {
    double alpha = (2*PI*getID(t[i]))/26;
    fa[i] = cd(cos(alpha), sin(alpha));
  }
  reverse(p.begin(), p.end());
  int k = 0;
  for (int i=0; i<np; ++i) {
    if (p[i] != '*') {
      double alpha = (2*PI*getID(p[i]))/26;
      fb[i] = cd(cos(alpha), -sin(alpha));
      ++k;
    } else {
      fb[i] = cd(0, 0);
    }
  }
  int n = 1;
  while (n < (nt + np))
    n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fft(fa, false);
  fft(fb, false);
  for (int i=0; i < n; ++i)
    fa[i] = fa[i]*fb[i];
  fft(fa, true);
  vector<bool> result(nt-np+1);
  for (int i=0; i<nt-np+1; ++i) {
    result[i] = (int(fa[np-1+i].a + 1e-9) == k);
  }
  return result;
}