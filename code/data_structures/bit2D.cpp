#include <bits/stdc++.h>

using namespace std;

namespace BIT2DRangeQuery {
    #define MAXN 1010
    #define MAXM 1010

    int n, m;
    // MAXN is the largest possible number of rows
    // MAXM is the largest possible number of columns
    int BIT[MAXN][MAXM];

    int query(int idx, int idy) {
	    for (int x {idx}; x > 0; x -= x & -x) {
		    for (int y {idy}; y > 0; y -= y & -y) {
			    // Query logic	
		    }
	    }
    }

    int range_query(int ix, int iy, int ex, int ey) {
	    // Do the query for (xe, ye) and remove the excess if needed with the queries
	    // (ex, iy - 1), (ix - 1, ey) and then add (ix - 1, iy - 1)
    }

    void update(int idx, int idy, int k) {
	    for (int x {idx}; x <= n; x += x & -x) {
		    for (int y {idy}; y <= m; y += y & -y) {
			    // Update logic
		    }
	    }
    }
}
