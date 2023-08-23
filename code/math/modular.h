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
