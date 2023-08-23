#include <bits/stdc++.h>
#include "modular.h"
using namespace std;
const int MOD = 1000000007;
/*
Number of correct bracket sequence consisting of n opening and n closing brackets.
The number of rooted full binary trees with n+1 leaves (vertices are not numbered). A rooted binary tree is full if every vertex has either two children or no children.
The number of ways to completely parenthesize n+1 factors.
The number of triangulations of a convex polygon with n+2 sides (i.e. the number of partitions of polygon into disjoint triangles by using the diagonals).
The number of ways to connect the 2n points on a circle to form n disjoint chords.
The number of non-isomorphic full binary trees with n internal nodes (i.e. nodes having at least one son).
The number of monotonic lattice paths from point (0, 0) to point (n, n) in a square lattice of size n*n, which do not pass above the main diagonal (i.e. connecting (0, 0) to (n, n)).
Number of permutations of length n that can be stack sorted (i.e. it can be shown that the rearrangement is stack sorted if and only if there is no such index i < j < k, such that a_k < a_i < a_j).
The number of non-crossing partitions of a set of n elements.
The number of ways to cover the ladder 1..n  using n rectangles (The ladder consists of n columns, where i-th column has a height i).
*/
i64 inv(i64 a){
  i64 inv_x, y;
  extGcd(a, MOD, inv_x, y);
  return (inv_x%MOD + MOD)%MOD;
}
const int MAXN = 4000010;
i64 fat[MAXN], ifat[MAXN];
void init(){
  fat[0] = 1;
  for(int i=1; i<MAXN; i++)
    fat[i] = (fat[i-1]*i)%MOD;
  ifat[MAXN - 1] = inv(fat[MAXN - 1]);
  for(int i=MAXN-2; i>=0; i--)
    ifat[i] = (ifat[i+1]*(i+1))%MOD;
  assert(ifat[0] == 1);
}
i64 C(int n, int k){
  if(k > n)
    return 0;
  return (fat[n]*((ifat[k]*ifat[n-k])%MOD))%MOD;
}
i64 catalan(int n){
  return (C(2*n, n) - C(2*n, n-1) + MOD)%MOD;
}
i64 f(int x1, int y1, int x2, int y2){
  int y = y2 - y1, x = x2 - x1;
  if(y < 0 or x < 0)
    return 0;
  return C(x + y, x);
}
// o = number of '(', c = number of ')', k = fixed prefix of '(' extra
// Catalan Generalization, open[i] >= close[i] for each 0 <= i < o + c + k
// where open[i] is number of '(' in prefix until i 
// and close[i] is number of ')'
i64 catalan2(int o, int c, int k){
  int x = o + k - c;
  if(x < 0)
    return 0;
  return (f(k, 0, o+k, c) - f(k, 0, o+k-x-1, c + x + 1) + MOD)%MOD;
}