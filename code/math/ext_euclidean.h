#include <bits/stdc++.h>
#include "basic_math.h"
using namespace std;
using i64 = long long;
i64 extGcd(i64 a, i64 b, i64 &x, i64 &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	i64 g = extGcd(b, a%b, y, x);
	y -= x*(a/b);
	return g;
}
//a*x + b*y = g
//a*(x-(b/g)*k) + b*(y+(a/g)*k) = g
bool dioEq(i64 a, i64 b, i64 c, i64 &x0, i64 &y0, i64 &g) {
  g = extGcd(abs(a), abs(b), x0, y0);
  if (c % g) return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}
inline void shift(i64 &x, i64 &y, i64 a, i64 b, i64 cnt) {
  x += cnt * b;
  y -= cnt * a;
}
// a1 + m1*x = a2 + m2*y
// Find the first moment that both are equal
i64 findMinimum(i64 a1, i64 m1, i64 a2, i64 m2){
  i64 a = m1, b = -m2, c = a2 - a1;
  i64 x, y, g;
  if (!dioEq(a, b, c, x, y, g))
    return -1;
  a /= g;
  b /= g;
  int sa = a > 0 ? +1 : -1;
  int sb = b > 0 ? +1 : -1;
  shift(x, y, a, b, -x/b);
  if(x < 0) 
    shift(x, y, a, b, sb);
  if(y < 0){
    shift(x, y, a, b, y/a);
    if(y < 0)
      shift(x, y, a, b, -sa);
    if(x < 0)
      return -1;
  }
  return a*x*g;
}
i64 findAllSolutions(i64 a, i64 b, i64 c, i64 minx, i64 maxx, i64 miny, i64 maxy){
	i64 x, y, g;
	if(a==0 or b==0){
		if(a==0 and b==0)
			return (c==0)*(maxx-minx+1)*(maxy-miny+1);
		if(a == 0)
			return (c%b == 0)*(maxx-minx+1)*(miny<=c/b and c/b<=maxy);
		return (c%a == 0)*(minx<=c/a and c/a<=maxx)*(maxy-miny+1);
	}
	if (!dioEq(a, b, c, x, y, g))
		return 0;
	a /= g;
	b /= g;
	int sign_a = a > 0 ? +1 : -1;
	int sign_b = b > 0 ? +1 : -1;
	shift(x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift(x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	i64 lx1 = x;
	shift(x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift(x, y, a, b, -sign_b);
	i64 rx1 = x;
	shift(x, y, a, b, -(miny - y) / a);
	if (y < miny)
		shift(x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	i64 lx2 = x;
	shift(x, y, a, b, -(maxy - y) / a);
	if (y > maxy)
		shift(x, y, a, b, sign_a);
	i64 rx2 = x;
	if (lx2 > rx2)
		swap(lx2, rx2);
	i64 lx = max(lx1, lx2);
	i64 rx = min(rx1, rx2);
	if (lx > rx)
		return 0;
	return (rx - lx) / abs(b) + 1;
}
