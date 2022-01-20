#include <iostream>
#include <vector>
using namespace std;

int s, n;
vector<int> nums;
vector<bool> triat;

void escriu() {
  cout << "{";
  bool first = true;
  for (int i = 0; i < n; ++i) {
    if (triat[i]) {
      if (first) first = false;
      else cout << ",";
      cout << nums[i];
    }
  }
  cout << "}" << endl;
}

void suma(int i, int sum) {
  if (i == n){
    if (sum == s) escriu();
    return;
  }

  triat[i] = false;
  sum += triat[i];
  suma(i + 1, sum);
  triat[i] = true;
  suma(i + 1, sum + nums[i]);
}

int main() {
  cin >> s >> n;
  nums = vector<int>(n);
  triat = vector<bool>(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  suma(0, 0);
}
