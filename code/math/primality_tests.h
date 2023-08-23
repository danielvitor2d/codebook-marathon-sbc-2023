#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 binpow(i64 b, i64 e, i64 m) {
  i64 ans = 1;
  b %= m;
  while (e) {
    if (e & 1) ans = (ans * b) % m;
    b = (b * b) % m;
    e >>= 1;
  }
  return ans;
}
bool probablyPrimeFermat(int n, int iter=5) {
  if (n < 4)
    return n == 2 || n == 3;
  for (int i = 0; i < iter; i++) {
    int a = 2 + rand() % (n - 3);
    if (binpow(a, n - 1, n) != 1)
      return false;
  }
  return true;
}