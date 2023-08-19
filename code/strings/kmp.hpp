#include <bits/stdc++.h>

using namespace std;

namespace KMP {
    // Runs in O(n)
    vector<int> kmp(const string &s) {
	    vector<int> pi(s.size());

	    for (int i {1}, j {}; i < (int) s.size(); ++i) {
		    while (j > 0 && s[i] != s[j]) {
			    j = pi[j - 1];
		    }

            if (s[i] == s[j]) {
                ++j;
            }

		    pi[i] = j;
	    }

        return pi;
    }

    // Runs in O(n)
    vector<int> ocurrences(const string &s, const string &t) {
	    vector<int> pi {kmp(s + "#")}, matches;

	    for (int i {}, j {}; i < (int) t.size(); ++i) {
		    while (j > 0 && t[i] != s[j]) {
			    j = pi[j - 1];
		    }

		    if (t[i] == s[j]) {
			    ++j;
		    }

		    if (j == (int) s.size()) {
			    matches.push_back(i - j + 1);
		    }
	    }

	    return matches;
    }

    // Runs in O(n)
    vector<int> count_prefixes(const string &s) {
	    int n {(int) s.size()};
	    vector<int> ans(n + 1), pi {kmp(s)};

	    for (int i {}; i < n; ++i) {
		    ++ans[pi[i]];
	    }

	    for (int i {n - 1}; i > 0; --i) {
		    ans[pi[i - 1]] += ans[i];
	    }

	    for (int i {1}; i <= n; ++i) {
		    ans[i - 1] = ans[i] + 1;
	    }

	    ans.pop_back();

	    return ans;
    }

    // Runs in O(n)
    string compress(const string &s) {
	    int n {(int) s.size()};
	    vector<int> pi {kmp(s)};

	    int k {n - pi.back()};

	    if (n % k != 0) {
		    return s;
	    }

	    return s.substr(0, k);
    }
}
