#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
using namespace std;
using i64 = long long;
using ii = pair<int, int>;
using ll = pair<i64, i64>;
// separador -> |

template<typename T> struct rmq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] <= v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1)-__builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	rmq() {}
	rmq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i-msb(at&-at), i) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
			t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int index_query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int x = l/b+1, y = r/b-1;
		if (x > y) return op(small(l+b-1), small(r));
		int j = msb(y-x+1);
		int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		return op(ans, small(r));
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};

struct SuffixArray {
  vector<int> SA, LCP;
  string s;
  SuffixArray (const string &s): s(s) {
    SA = suffix_array_construction(s);
    LCP = lcp_construction(s, SA);
  }
  vector<int> sort_cyclic_shifts(const string& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
      cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
      p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
      if (s[p[i]] != s[p[i-1]])
        classes++;
      c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
      for (int i = 0; i < n; i++) {
        pn[i] = p[i] - (1 << h);
        if (pn[i] < 0)
          pn[i] += n;
      }
      fill(cnt.begin(), cnt.begin() + classes, 0);
      for (int i = 0; i < n; i++)
        cnt[c[pn[i]]]++;
      for (int i = 1; i < classes; i++)
        cnt[i] += cnt[i-1];
      for (int i = n-1; i >= 0; i--)
        p[--cnt[c[pn[i]]]] = pn[i];
      cn[p[0]] = 0;
      classes = 1;
      for (int i = 1; i < n; i++) {
        pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
        pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
        if (cur != prev)
          ++classes;
        cn[p[i]] = classes - 1;
      }
      c.swap(cn);
    }
    return p;
  }
  vector<int> suffix_array_construction(string s) {
    s += '$';
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
  }
  vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
      rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = p[rank[i] + 1];
      while (i + k < n && j + k < n && s[i+k] == s[j+k])
        k++;
      lcp[rank[i]] = k;
      if (k)
        k--;
    }
    return lcp;
  }
  vector<int> getSA() {
    return SA;
  }
  vector<int> getLCP() {
    return LCP;
  }
};

int n;
rmq<int> RMQ;
vector<int> sa, lcp;

// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D
i64 f(i64 k) { return k*(k+1)/2; }

// dah pra fazer small to large
// p eh a profundidade da posicao atual na suffix tree
i64 dfs(int L, int R, int p) { // dfs na suffix tree chamado em pre ordem
  int ext = L != R ? RMQ.query(L, R-1) : n - sa[L];

  // Tem 'ext - p' substrings diferentes que ocorrem 'R-L+1' vezes
  // O LCP de todas elas eh 'ext'
  i64 ans = (ext-p)*f(R-L+1);

  // L eh terminal, e folha sse L == R
  if (sa[L]+ext == n) L++;

  // se for um SA de varias strings separadas como s#t$u&, usar no lugar do if de cima
  //	(separadores < 'a', diferentes e inclusive no final)
  // while (L <= R && (sa[L]+ext == n || s[sa[L]+ext] < 'a')) {
  //   L++;
  // }

  while (L <= R) {
    int idx = L != R ? RMQ.index_query(L, R-1) : -1;
    if (idx == -1 or lcp[idx] != ext) idx = R;

    ans += dfs(L, idx, ext);
    L = idx+1;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

}