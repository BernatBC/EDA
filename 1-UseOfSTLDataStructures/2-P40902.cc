#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  string nom;
  map <string, int> jugadors;
  while (cin >> nom) {
    string funcio;
    cin >> funcio;

    if (funcio == "enters") {
      if (jugadors.find(nom) != jugadors.end()) cout << nom << " is already in the casino" << endl;
      else {
        jugadors[nom] = 0;
      }
    }
    else if (funcio == "wins") {
      auto it = jugadors.find(nom);
      int x;
      cin >> x;
      if (it == jugadors.end()) cout << nom << " is not in the casino" << endl;
      else {
        it->second += x;
      }
    }
    else if (funcio == "leaves") {
      if (jugadors.find(nom) == jugadors.end()) cout << nom << " is not in the casino" << endl;
      else {
        cout << nom << " has won " << jugadors[nom] << endl;
        jugadors.erase(nom);
      }
    }
  }
  cout << "----------" << endl;
  map<string, int>::const_iterator it = jugadors.begin();
  while (it != jugadors.end()) {
    cout << it->first << " is winning " << it->second << endl;
    ++it;
  }
}
