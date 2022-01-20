#include <iostream>
#include <vector>
using namespace std;

vector<int> mult(vector<int> a, vector<int> b, int m) {
  vector<int> c(4);
  c[0] = (a[0]*b[0] + a[1]*b[2])%m;
  c[1] = (a[0]*b[1] + a[1]*b[3])%m;
  c[2] = (a[2]*b[0] + a[3]*b[2])%m;
  c[3] = (a[2]*b[1] + a[3]*b[3])%m;
  return c;
}

vector<int> pot(vector<int> a, int n, int m) {
  vector<int> c(4);
  c[0] = c[3] = 1;
  c[1] = c[2] = 0;
  if (n == 0) return c;
  if (n%2 == 0) {
    c = pot(a, n/2, m);
    return mult(c, c, m);
  }
  c = pot(a, n - 1, m);
  return mult(c, a, m);
}

int fib(int n, int m) {
  if (n < 2) return n;
  vector<int> c(4);
  c[0] = c[1] = c[2] = 1;
  c[3] = 0;
  c = pot(c, n, m);
  return c[2];
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    cout << fib(n, m) << endl;
  }
}
