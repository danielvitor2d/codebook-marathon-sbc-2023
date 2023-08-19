#include <bits/stdc++.h>

using namespace std;

namespace BITRangeQuery {
    #define MAXN int(1e5)

    int n;
    int BIT[MAXN]; // MAXN is the largest possible number of elements

    // Runs in O(log n)
    int query(int idx) {
	    for (; idx > 0; idx -= idx & -idx) {
		    // Query logic
	    }
    }

    // Runs in O(log n)
    int range_query(int l, int r) {
	    // Do the query for r and remove the excess with the query for l - 1
    }

    // Runs in O(log n)
    void update(int idx, int k) {
	    for (; idx <= n; idx += idx & -idx) {
		    // Update logic
	    }
    }
}

namespace BITPointQuery {
    #define MAXN int(1e5)

    int n;
    int BIT[MAXN]; // MAXN is the largest possible number of elements

    // Runs in O(log n)
    void update(int idx, int k) {
	    for (; idx <= n; idx += idx & -idx) {
		    // Update logic
	    }
    }

    // Runs in O(log n)
    void range_update(int l, int r, int k) {
	    int undo {};

	    update(l, k);
	    update(r + 1, undo);
    }

    // Runs in O(log n)
    int point_query(int idx) {
	    for (; idx > 0; idx -= idx & -idx) {
		    // Query logic
	    }
    }
}
