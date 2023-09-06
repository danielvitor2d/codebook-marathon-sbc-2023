#include <bits/stdc++.h>
using namespace std;
// given two numbers n and r, count the number of integers in interval [1; r] that are relatively prime to n
// O(sqrt(n))
int solve(int n, int r) {
  vector<int> p;
  for (int i=2; i*i<=n; ++i)
    if (n%i == 0) {
      p.push_back(i);
      while (n % i == 0)
        n /= i;
    }
  if (n > 1)
    p.push_back(n);
  int sum = 0;
  for (int mask = 1; mask < (1 << p.size()); ++mask) {
    int mult = 1, bits = 0;
    for (int i=0; i < (int)p.size(); ++i) {
      if (mask & (1 << i)) {
        ++bits;
        mult *= p[i];
      }
    }
    int curr = r / mult;
    if (bits & 1)
      sum += curr;
    else
      sum -= curr;
  }
  return r - sum;
}
int solve2(int n, int r, const vector<int> &a) {
  int sum = 0;
  for (int mask = 1; mask < (1 << n); ++mask) {
    int l = 1, bits = 0;
    for (int i=0; i < n; ++i) {
      if (mask & (1 << i)) {
        ++bits;
        l = lcm(l, a[i]);
      }
    }
    int curr = r / l;
    if (bits & 1)
      sum += curr;
    else
      sum -= curr;
  }
  return sum;
}