#include <bits/stdc++.h>
using namespace std;
namespace FloydWarshall {
  #define MAXN 1000 // MAXN is the largest possible number of nodes
  #define INF INT_MAX
  int dp[MAXN][MAXN];
  int n, m;
  // Runs in O(V^3)
  void floyd_warshall() {
    cin >> n >> m;
    for (int i {}; i < n; ++i) {
      for (int j {}; j < n; ++j) {
        if (i == j) {
          dp[i][j] = 0;
        } else {
          dp[i][j] = INF;
        }
      }
    }
    for (int i {}; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      dp[u][v] = w;
      dp[v][u] = w;
    }
    for (int k {}; k < n; ++k) {
      for (int i {}; i < n; ++i) {
        for (int j {}; j < n; ++j) {
          if (dp[i][k] < INF && dp[k][j] < INF) {
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
          }
        }
      }
    }
  }
}