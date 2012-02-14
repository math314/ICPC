#include <iostream>

using namespace std;

int p, q, a;

int solve(int n, int d, int prod, int sum) {
  int cnt=0;
  for (int i=d; prod*i<=a; i++) {
    int left = p * (prod * i);
    int right = sum * i + prod;
    if (left < right * q) { continue; }
    if (left == right * q) { cnt++; continue; }
    if (n == 1) { continue; }
    cnt += solve(n-1, i, prod * i, right);
  }

  return cnt;
}

int main() {
  int n;
  while (cin >> p >> q >> a >> n, (p || q || a || n)) {
    cout << solve(n, 1, 1, 0) << endl;
  }

  return 0;
}
