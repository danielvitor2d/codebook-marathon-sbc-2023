#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
using namespace std;
using i64 = long long;
using ii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n; cin >> n;

  int sum = 0;
  vector<ii> v(n);
  for (auto &[a, b] : v) {
    cin >> a >> b;
    sum += a;
  }

  for (int i = 1; i <= sum; ++i) {
    do {
      bool show = true;
      int at = i;

      for (auto [a, b] : v) {
        if (at<a) show = false;
        at -= b;
      }

      if (show) {
        cout << i << '\n';
        return 0;
      }

    } while (next_permutation(all(v)));
  }

  return 0;
}