#include <bits/stdc++.h>
#include "./kmp.hpp"

using namespace std;

namespace KMPAutomaton {
    #define K 26

    int get_id(char ch) {
	    return ch - 'a';
    }

    vector<vector<int>> automaton(const string &s) {
	    int n {(int) s.size()};

	    vector<int> pi {KMP::kmp(s)};
	    vector<vector<int>> aut(n + 1, vector<int>(K));

	    aut[0][get_id(s[0])] = 1;

	    for (int i {1}; i < n; ++i) {
		    for (int c {}; c < K; ++c) {
			    aut[i][c] = c == get_id(s[i]) ? i + 1 : aut[pi[i - 1]][c];
		    }
	    }

	    for (int c {}; c < K; ++c) {
		    aut[n][c] = aut[pi[n - 1]][c];
	    }

	    return aut;
    }
}
