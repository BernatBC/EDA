#include <iostream>
#include <queue>
using namespace std;

int main() {
  priority_queue<int> num;
  char op;
  while(cin >> op) {
    if (op == 'S') {
      int a;
      cin >> a;
      num.push(a);
    }
    else if (op == 'R') {
      if (not num.empty()) num.pop();
      else cout << "error!" << endl;
    }
    else if (op == 'I') {
      int a;
      cin >> a;
      if (not num.empty()) {
        int x = num.top();
        x += a;
        num.pop();
        num.push(x);
      }
      else cout << "error!" << endl;
    }
    else if (op == 'D') {
      int a;
      cin >> a;
      if (not num.empty()) {
        int x = num.top();
        x -= a;
        num.pop();
        num.push(x);
      }
      else cout << "error!" << endl;
    }
    else if (op == 'A') {
      if (num.empty()) cout << "error!" << endl;
      else cout << num.top() << endl;
    }
  }
}
