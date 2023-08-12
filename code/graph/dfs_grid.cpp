#include <bits/stdc++.h>
using namespace std;
namespace DFSGrid {
  #define MAXN 1000 // MAXN is the largest possible number of rows and columns for a square matrix
  int l, c;
  int di[] = {1, 0, -1, 0};
  int dj[] = {0, 1, 0, -1};
  int board[MAXN][MAXN];
  bitset<MAXN> visited[MAXN];
  bool is_cell_valid(int i, int j) {
    if (i < 0 || i >= l || j < 0 || j >= c) {
      return false;
    } else if (visited[i][j]) {
      return false;
    }
    return true;
  }
  // 0-indexed
  // Runs in O(nm)
  void dfs(int i, int j) {
    visited[i][j] = true;
    for (int k = 0; k < 4; ++k) {
      int ni = i + di[k];
      int nj = j + dj[k];
      if (is_cell_valid(ni, nj)) {
        dfs(ni, nj);
      }
    }
  }
}