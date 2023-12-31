#include <bits/stdc++.h>
using namespace std;
namespace NearestPairOfPoints {
  template <typename T>
  struct Point2D { T x, y; };

  template <typename T>
  using ptt = pair<T, T>;

  template <typename T>
  double find_minimum_distance(vector<Point2D<T>> points) {
    typedef ptt<T> ptt;
    int n {(int) points.size()};
    // Sort them according to their x-coordinates in ascending order
    sort(points.begin(), points.end());
    int fp {};
    set<ptt> active_points;
    double ans {distance_between_points(points[0], points[1])};
    for (int i {}; i < n; ++i) {
	  while (fp < i && points[i].x - points[fp].x >= ans) {
	    active_points.erase({points[fp].y, fp});
	    ++fp;
	  }
	  auto it {active_points.lower_bound({points[i].y - ans, 0})};
	  while (it != active_points.end() && it->first < points[i].y + ans) {
	    ans = min(ans, distance_between_points(points[i], points[it->second]));
	    ++it;
	  }
	  active_points.insert({points[i].y, i});
    }
    return ans;
  }
}
