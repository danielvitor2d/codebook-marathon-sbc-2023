#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
using namespace std;
using ii = pair<int, int>;
using i64 = long long;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n; cin >> n;
  vector<ii> v(n);
  for (auto &[a, b] : v) {
    cin >> a >> b;
  }

  sort(v.begin(), v.end(), [](ii a, ii b) {
    if (a.se-a.fi != b.se-b.fi) return a.se-a.fi < b.se-b.fi;
    return a.fi < b.fi;
  });

  i64 ans = 0, at = 0;
  for (auto [a, b] : v) {
    if (at < a) ans += a-at, at = a-b;
    else at -= b;
  }

  cout << ans << '\n';

  return 0;
}