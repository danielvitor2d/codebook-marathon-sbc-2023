#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
  return rand() % (b-a+1) + a;
}

int main(int argc, char **argv) {
  srand(atoi(argv[1]));

  int n = rand(1, 10);
  cout << n << '\n';

  for (int i = 0; i < n; ++i) {
    int a = rand(1, 10), b = rand(1, 10);
    if (a<b) swap(a, b);
    cout << a << ' ' << b << '\n';
  }

  return 0;
}