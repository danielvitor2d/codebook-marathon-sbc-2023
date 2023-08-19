#include <bits/stdc++.h>

using namespace std;

namespace Manacher {
    typedef pair<int, int> pii;

    // Runs in O(n)
    vector<int> manacher(const string &s) {
        int n {(int) s.size()};

        vector<int> d1(n);

        int l {}, r {-1};

        for (int i {}; i < n; ++i) {
            int k {i > r ? 1 : min(d1[l + r - i], r - i + 1)};

            while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) {
                ++k;
            }

            d1[i] = k;

            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }

        vector<int> d2(n);

        l = 0;
        r = -1;

        for (int i {}; i < n; ++i) {
            int k {i > r ? 0 : min(d2[l + r - i + 1], r - i + 1)};

            while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) {
                ++k;
            }

            d2[i] = k;

            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }

        vector<int> ans(n * 2 - 1);

        for (int i {}; i < n; ++i) {
            ans[2 * i] = 2 * d1[i] - 1;
        }

        for (int i {}; i < n - 1; ++i) {
            ans[2 * i + 1] = 2 * d2[i + 1];
        }

        return ans;
    }

    // Runs in O(1)
    bool is_palindrome(const vector<int> &m, int i, int j) {
	    return m[i + j] >= j - i + 1;
    }

    // Runs in O(n)
    pii longest_palindrome(const vector<int> &m) {
	    int ans {}, length {};

	    for (int i {}; i < (int) m.size(); ++i) {
		    if (m[i] > length) {
			    length = m[i];
			    ans = i;
		    }
	    }

	    length /= 2;

	    if (ans % 2 == 0) {
		    ans /= 2;

		    return {ans - length, ans + length};
	    }

	    ans += 1;
	    ans /= 2;

	    return {ans - length, ans + length - 1};
    }
}
