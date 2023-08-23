#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
using ui32 = uint32_t;
namespace ModHash{
  const ui64 MOD = (1ll<<61) - 1;
  ui64 modmul(ui64 a, ui64 b){
    ui64 l1 = (ui32)a, h1 = a>>32, l2 = (ui32)b, h2 = b>>32;
    ui64 l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    ui64 ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
    ret = (ret & MOD) + (ret>>61);
    ret = (ret & MOD) + (ret>>61);
    return ret-1;
  }
};
ui64 modMul(ui64 a, ui64 b, ui64 MOD) {
	return (__uint128_t)a*b%MOD;
}
ui64 binpow(ui64 base, ui64 exp, ui64 MOD) {
	base %= MOD;
	ui64 res = 1;
	while (exp > 0) {
		if (exp & 1) res = modMul(res, base, MOD);
		base = modMul(base, base, MOD);
		exp >>= 1;
	}
	return res;
}
ui64 bigExp(ui64 base, std::string exp, ui64 MOD) {
	base %= MOD;
	ui64 ans = 1LL;
	for (char c : exp) {
		ans = binpow(ans, 10LL, MOD);
		ans = modMul(ans, binpow(base, c-'0', MOD), MOD);
	}
	return ans;
}
// O(log(min(a, b)))
i64 gcd(i64 a, i64 b) {
  while (b) { a %= b; swap(a, b); }
  return a;
}
i64 binaryGcd(i64 a, i64 b) {
  if (!a || !b) return a | b;
  unsigned shift = __builtin_ctzll(a | b);
  a >>= __builtin_ctzll(a);
  do {
    b >>= __builtin_ctzll(b);
    if (a > b) swap(a, b);
    b -= a;
  } while (b);
  return a << shift;
}
i64 lcm(i64 a, i64 b) {
  return a / gcd(a, b) * b;
}