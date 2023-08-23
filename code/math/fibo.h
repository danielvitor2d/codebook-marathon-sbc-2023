#include <bits/stdc++.h>
using namespace std;
// Cassini's identity
// F(n-1)*F(n+1)-F(n)^2=(-1)^n

// The "addition" rule:
// F(n+k)=F(k)*F(n+1)+F(k-1)*F(n)
// when k = n:
// F(2n)=F(n)*(F(n+1)+F(n-1))
// F(nk) is multiple of F(n), for any positive integer k
// if F(m) is multiple of F(n), then m is multiple of n

// GCD identity:
// GCD(F(m), F(n)) = F(GCD(m,n))

// Binet's formula
// A = (1 + sqrt(5)) / 2
// B = (1 - sqrt(5)) / 2
// F(n) = (A ^ n - B ^n) / sqrt(5)

// O(logn) - {F(n), F(n+1)}
pair<int, int> fib (int n) {
  if (n == 0)
    return {0, 1};

  auto p = fib(n >> 1);
  int c = p.first * (2 * p.second - p.first);
  int d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}