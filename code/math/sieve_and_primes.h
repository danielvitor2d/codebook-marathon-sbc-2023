#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 ns;
int np;
bitset<10000010> bs;
vector<i64> primes;
void sieve(i64 l) {
  ns = l+1;
  bs.set();
  primes.clear();
  bs[0] = bs[1] = 0;
  for (i64 i = 2; i < ns; ++i) if (bs[i]) {
    for (i64 j = i*i; j < ns; j += i)
      bs[j] = 0;
    primes.push_back(i);
  }
  np = primes.size();
}
bool isPrime(i64 n) {
  if (n < ns)
    return bs[n];
  for (i64 p : primes) {
    if (p * p > n) return true;
    if (n%p == 0) return false;
  }
  return true;
}
vector<i64> primeFactors(i64 n) {
  vector<i64> factors;
  for (i64 p : primes) {
    if (p * p > n) break;
    while (n%p == 0LL) {
      n /= p;
      factors.push_back(p);
    }
  }
  if (n != 1LL) factors.push_back(n);
  return factors;
}
i64 numDiv(i64 n) {
  i64 ans = 1;
  for (i64 p : primes) {
    if (p*p > n) break;
    i64 f = 0;
    while (n%p == 0LL) {
      n /= p;
      f++;
    }
    ans *= (f+1LL);
  }
  return (n != 1LL) ? 2LL*ans : ans;
}
i64 sumDiv(i64 n) {
  i64 ans = 1;
  for (i64 p : primes) {
    if (p*p > n) break;
    i64 power = p;
    while (n%p == 0LL) {
      n /= p;
      power *= p;
    }
    ans *= (power - 1LL)/(p - 1LL);
  }
  if (n != 1LL)
    ans *= (n*n - 1LL)/(n - 1LL);
  return ans;
}
int mobius[1000010];
void sieveMobius(i64 l) {
  sieve(l);
  mobius[1] = 1;
  for(int i=2; i<=l; i++)
    mobius[i] = 0;
  for(i64 p: primes){
    if(p > l) break;
    for(i64 j = p; j <= l; j += p){
      if(mobius[j] != -1){
        mobius[j]++;
        if(j%(p*p) == 0)
          mobius[j] = -1;
      }
    }
  }
  for(int i=2; i<=l; i++){
    if(mobius[i] == -1)
      mobius[i] = 0;
    else if(mobius[i]%2 == 0)
      mobius[i] = 1;
    else
      mobius[i] = -1;
  }
}
// O((R - L + 1)loglog(R) + sqrt(R)loglog(sqrt(R)))
vector<char> segmentedSieve(long long L, long long R) {
  long long lim = sqrt(R);
  vector<char> mark(lim + 1, false);
  vector<long long> primes;
  for (long long i = 2; i <= lim; ++i) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (long long j = i * i; j <= lim; j += i)
        mark[j] = true;
    }
  }
  vector<char> isPrime(R - L + 1, true);
  for (long long i : primes)
    for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
      isPrime[j - L] = false;
  if (L == 1)
    isPrime[0] = false;
  return isPrime;
}
void linearSieve() {
  const int N = 10000000;
  vector<int> lp(N+1);
  vector<int> pr;
  for (int i=2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] == lp[i]) {
        break;
      }
    }
  }
}