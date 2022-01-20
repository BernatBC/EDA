#include <iostream>
using namespace std;

//n^k*mod(m)
int potencia(int n, int k, int m) {
  if (k == 0) return 1;
  int p = potencia(n, k/2, m);
  p = p*p%m;
  if (k%2 == 1) p = p*n%m;
  return p;
}

int main() {
  int n, k, m;
  while (cin >> n >> k >> m) {
    cout << potencia(n, k, m) << endl;
  }
}
