#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int K = 2;
const int SZ = 32;

struct Vertex {
  vector<Vertex*> next;
  bool isEnd = false;

  int getValue(char x) {
    return x - '0';
  }

  Vertex(bool isEnd = false) {
    this->next.assign(K, nullptr);
    this->isEnd = isEnd;
  }

  Vertex(vector<Vertex*> &next, bool isEnd = false) {
    this->next = next;
    this->isEnd = isEnd;
  }

  Vertex* insert(const string &key, int len) {
    if (len == key.size()) {
      return new Vertex(this->next, true);
    }

    vector<Vertex*> newVersionNext = this->next;

    int val = getValue(key[len]);

    if (!newVersionNext[val]) {
      newVersionNext[val] = new Vertex();
    }

    newVersionNext[val] = newVersionNext[val]->insert(
      key, len + 1
    );

    return new Vertex(newVersionNext);
  }

  bool findKey(const string &key, int len) {
    if (key.size() == len) {
      return this->isEnd;
    }

    int val = getValue(key[len]);
    if (this->next[val] == nullptr) {
      return false;
    }

    return this->next[val]->findKey(key, len + 1);
  }

  void dfs(const string& prefix = "") {
    if (this->isEnd) {
      cout << prefix << endl;
    }

    for (int i = 0; i < K; i++) {
      if (this->next[i]) {
        char c = i + '0';
        this->next[i]->dfs(prefix + c);
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  Vertex* root = new Vertex();

  vector<Vertex*> roots;
  roots.push_back(root);

  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    Vertex* newRoot = roots.back()->insert(s, 0);
    roots.push_back(newRoot);
  }

  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    int t; cin >> t;
    string s; cin >> s;

    Vertex* currRoot = roots[t + 1];

    cout << currRoot->findKey(s, 0) << '\n';
  }

  roots.back()->dfs();
}