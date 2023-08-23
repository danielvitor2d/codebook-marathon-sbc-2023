#include <bits/stdc++.h>
#include "ext_euclidean.h"
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
const i64 MOD = 1e9+7;
inline i64 modSum(i64 a, i64 b, i64 mod = MOD) {
  return (a+b >= mod ? a+b-mod : a+b);
}
inline i64 modSub(i64 a, i64 b, i64 mod = MOD) {
  return (a-b < 0 ? a-b+mod : a-b);
}
inline i64 modMul(i64 a, i64 b, i64 mod = MOD) {
  return (a*b)%mod;
}
i64 inv_mod(i64 a, i64 m = MOD) {
  i64 x, y;
  extGcd(a, m, x, y);
  return (x%m + m)%m;
}
i64 modDiv(i64 a, i64 b, i64 mod = MOD) {
  return modMul(a, inv_mod(b, mod), mod);
}
//O(log(a))
i64 bigModMul(i64 a, i64 b, i64 mod = MOD) {
	i64 ans = 0LL;
	b %= mod;
	while (a > 0) {
		if (a & 1) ans = modSum(ans, b);
		b = modMul(b, 2LL);
		a >>= 1;
	}
	return ans;
}
ui64 bigModMul_2(ui64 a, ui64 b, i64 mod = MOD) {
	long double x;
	ui64 c;
	i64 r;
	if (a >= mod) a %= mod;
	if (b >= mod) b %= mod;
	x = a;
	c = (x * b) / mod;
	r = (i64) (a * b - c * mod) % (i64)mod;
	return (r < 0 ? r+mod : r);
}
int primitiveRoot(int p) {
  vector<int> fact;
  int phi = p-1,  n = phi;
  for (int i=2; i*i<=n; i++){
    if (n % i == 0) {
      fact.push_back (i);
      while (n % i == 0)
        n /= i;
    }
  }
  if (n > 1)
    fact.push_back (n);
  for (int res=2; res<=p; ++res) {
    bool ok = true;
    for (size_t i=0; i<fact.size() && ok; ++i)
      ok &= binpow(res, phi / fact[i], p) != 1;
    if (ok)  return res;
  }
  return -1;
}
// Return x  ->   a ^ x = b mod m
// Example: a = 5, m = 10^9 + 7
// Funciona melhor se 'a' for raiz primitiva de 'm'
int discreteLogarithm(int a, int b, int m) {
  a %= m, b %= m;
  int k = 1, add = 0, g;
  while ((g = gcd(a, m)) > 1) {
    if (b == k)
      return add;
    if (b % g)
      return -1;
    b /= g, m /= g, ++add;
    k = (k * 1ll * a / g) % m;
  }
  int n = sqrt(m) + 1;
  int an = 1;
  for (int i = 0; i < n; ++i)
    an = (an * 1ll * a) % m;
  unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }
  for (int p = 1, cur = k; p <= n; ++p) {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur)) {
      int ans = n * p - vals[cur] + add;
      return ans;
    }
  }
  return -1;
}