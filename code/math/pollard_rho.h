#include <bits/stdc++.h>
#include "miller_rabin.h"
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
ui64 pollard(ui64 n) {
	auto f = [n](ui64 x) { return (modMul(x, x, n) + 1) % n; };
	ui64 x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 or binaryGcd(prd, n) == 1) {
		if (x == y)
			x = ++i, y = f(x);
		if ((q = modMul(prd, max(x, y) - min(x, y), n)))
			prd = q;
		x = f(x), y = f(f(y));
	}
	return binaryGcd(prd, n);
}
vector<ui64> factor(ui64 n) {
	if (n == 1)
		return {};
	if (MillerRabin(n))
		return {n};
	ui64 x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}