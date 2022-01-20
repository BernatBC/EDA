#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Mat;
typedef vector<vector<vector<bool>>> Mat3;
typedef vector<vector<bool>> Mat_b;

Mat S;
Mat_b fila;
Mat_b colu;
Mat3 quad;

void escriu() {
  cout << endl;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      cout <<  (j ? " " : "") << S[i][j];
    }
    cout << endl;
  }
}

bool sudoku(int i, int j) {
  //Sudoku completat
  if (i == 9) {
    escriu();
    return true;
  }
  //Fila acabada
  if (j == 9) {
    return sudoku(i + 1, 0);
  }
  //Casella amb un número ja posat
  if (S[i][j]) {
    return sudoku(i, j + 1);
  }
  for (int x = 1; x <= 9; ++x) {
    if (not fila[i][x] and not colu[j][x] and not quad[i/3][j/3][x]) {
      S[i][j] = x;
      fila[i][x] = colu[j][x] = true;
      quad[i/3][j/3][x] = true;
      bool a = sudoku(i, j + 1);
      if (a) return true;
      S[i][j] = 0;
      fila[i][x] = colu[j][x] = false;
      quad[i/3][j/3][x] = false;
    }
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  cout << t << endl;
  while (t--) {
    S = Mat(9, vector<int>(9));
    fila = colu = Mat_b(9, vector<bool>(10, false));
    quad = Mat3(3, vector<vector<bool>>(3, vector<bool>(10, false)));
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        char c;
        cin >> c;
        if (c == '.') S[i][j] = 0;
        else {
          S[i][j] = c - '0';
          fila[i][c - '0'] = true;
          colu[j][c - '0'] = true;
          quad[i/3][j/3][c - '0'] = true;
        }
      }
    }
    sudoku(0, 0);
  }
}
