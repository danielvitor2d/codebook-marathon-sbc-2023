#include <bits/stdc++.h>
#include "basic_math.h"
using namespace std;
using u128 = __uint128_t;
bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
	uint64_t x = binpow(a, d, n);
	if (x == 1 or x == n - 1)
		return false;
	for (int r = 1; r < s; ++r) {
		x = modMul(x, x, n);
		if (x == n - 1)
			return false;
	}
	return true;
}
bool MillerRabin(uint64_t n) {
	if (n < 4) 
		return (n == 2 or n == 3);
	uint64_t d = n - 1;
	int s = __builtin_ctzll(d);
	d >>= s;
	for (uint64_t a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		// int a = 2 + rand() % (n - 3);  // nondeterministic version
		if (n == a)
			return true;
		if (check_composite(n, a, d, s)) 
			return false;
	}
	return true;
}
