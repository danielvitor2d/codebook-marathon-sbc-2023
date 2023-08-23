#include <bits/stdc++.h>
using namespace std;
namespace CoordinateCompression {
	// Runs in O(n log n)
	void coordinate_compression(vector<int> &v) {
		vector<int> aux(v);
		sort(aux.begin(), aux.end());
		unordered_map<int, int> ump;
		int cnt {1};
		for (int x : aux) {
			ump[x] = cnt++;
		}
		for (int &x : v) {
			x = ump[x];
		}
	}
}
