#include <bits/stdc++.h>
#include "./modular.h"
using namespace std;
// O(k)
i64 C1(int n, int k) {
  i64 ans = 1LL;
  for (int i = 1; i <= k; ++i)
    ans = (ans * (n - k + 1)) / i;
  return ans;
}
//O(n²)
vector<vector<i64>> C2(int maxn, int mod) {
  vector<vector<i64>> mat(maxn+1, vector<i64>(maxn+1, 0));
  mat[0][0] = 1;
  for (int n = 1; n <= maxn; ++n) {
    mat[n][0] = mat[n][n] = 1;
    for (int k = 1; k < n; ++k) {
      mat[n][k] = (mat[n-1][k-1] + mat[n-1][k]) % mod;
    }
  }
  return mat;
}
//O(N)
vector<int> fac, inv_fac;
void prevC3(int maxn, int mod){
  fac.resize(maxn + 1);
  fac[0] = 1;
  for (int i = 1; i <= maxn; i++)
    fac[i] = (fac[i - 1] * 1LL * i) % mod;
  inv_fac.resize(maxn + 1);
  inv_fac[maxn] = binpow(fac[maxn], mod - 2, mod);
  for (int i = maxn - 1; i >= 0; i--)
    inv_fac[i] = (inv_fac[i + 1] * 1LL * (i + 1)) % mod;
}
int C3(int n, int k, int mod){
  if (n < k) return 0;
  return (((fac[n] * 1LL * inv_fac[k]) % mod) * 1LL * inv_fac[n - k]) % mod;
}
//O(P*log(P))
//C4(n, k, p) = Comb(n, k)%p
vector<int> changeBase(int n, int p){
  vector<int> v;
  while (n > 0){
    v.push_back(n % p);
    n /= p;
  }
  return v;
}
int C4(int n, int k, int p){
  auto vn = changeBase(n, p);
  auto vk = changeBase(k, p);
  int mx = max(vn.size(), vk.size());
  vn.resize(mx, 0);
  vk.resize(mx, 0);
  prevC3(p - 1, p);
  int ans = 1;
  for (int i = 0; i < mx; i++)
    ans = (ans * 1LL * C3(vn[i], vk[i], p)) % p;
  return ans;
}
//O(P^k)
//C5(n, k, p, pk) = Comb(n, k)%(p^k)
int fat_p(i64 n, int p, int pk){
	vector<int> fat1(pk, 1);
    int res = 1;
    for(int i=1; i<pk; i++){
		if(i%p == 0)
			fat1[i] = fat1[i-1];
		else
			fat1[i] = (fat1[i-1]*1LL*i)%pk;
	}
	while(n > 1){
		res = (res*1LL*binpow(fat1[pk-1], n/pk, pk))%pk;
		res = (res*1LL*fat1[n%pk])%pk;
		n /= p;
	}
	return res;
}
i64 cnt(i64 n, int p){
	i64 ans = 0;
	while(n > 1){
		ans += n/p;
		n/=p;
	}
	return ans;
}
int C5(i64 n, i64 k, int p, int pk){
	i64 exp = cnt(n, p) - cnt(n-k, p) - cnt(k, p);
	int d = (fat_p(n-k, p, pk)*1LL*fat_p(k, p, pk))%pk;
	int ans = (fat_p(n, p, pk)*1LL*inv_mod(d, pk))%pk;
	return (ans*1LL*binpow(p, exp, pk))%pk;	
}