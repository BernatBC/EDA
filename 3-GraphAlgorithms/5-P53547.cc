#include <iostream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
typedef vector<vector<int>> matriu;

void alfils_dfs(matriu& m, int& cas, int& alf, int x, int y) {
  if (m[y][x] != -1) {
    //En el cas que la casella no correpongui a -1 (X), sumar nombre d'alfils, augmentar en 1 el nombre de caselles
    ++cas;
    alf += m[y][x];
    //Marquem la casella a -1 (X) per no tornar-la a visitar
    m[y][x] = -1;
    //Continuar amb el dfs
    alfils_dfs(m, cas, alf, x + 1, y + 1);
    alfils_dfs(m, cas, alf, x + 1, y - 1);
    alfils_dfs(m, cas, alf, x - 1, y + 1);
    alfils_dfs(m, cas, alf, x - 1, y + 1);
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int a, b;
    cin >> a >> b;
    //La matriu està envoltada de Xs per evitar consultes fora d'ella
    //La matriu de int tindrà a la seva posició el número d'alfils, o -1 a les caselles on correspon a X
    matriu m(b + 2, vector<int>(a + 2, -1));
    int caselles = 0;
    int alfils = 0;
    //Lectura del taulell
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) {
        string s;
        cin >> s;
        if (s == "X") m[j + 1][i + 1] = -1;
        else {
          m[j + 1][i + 1] = atoi(s.c_str());
          ++caselles;
          alfils += m[j + 1][i + 1];
        }
      }
    }
    bool rep_igual = true;
    if (caselles != 0) {
      //Comprovar si els alfils es poden repartir per totes les caselles a parts iguals
      if (alfils%caselles != 0) rep_igual = false;
      //Comprovar si a cada "bloc" (zona per on es pot moure un alfil en concret) es poden repartir a parts iguals
      for (int i = 1; i < a + 1 and rep_igual; ++i) {
        for (int j = 1; j < b + 1 and rep_igual; ++j) {
          if (m[j][i] != -1) {
            int cas = 0;
            int alf = 0;
            alfils_dfs(m, cas, alf, i, j);
            //Comprovar si els alfils es poden repartir per totes les caselles del bloc a parts iguals
            if (alf%cas != 0) rep_igual = false;
            //Comprovar si el nombre d'alfils per casella correspon al nombre d'alfils per casella de tot el taulell
            if (alfils/caselles != alf/cas) rep_igual = false;
          }
        }
      }
    }
    //Mostrar resultat
    cout << "Case " << i << ": ";
    if (rep_igual) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
