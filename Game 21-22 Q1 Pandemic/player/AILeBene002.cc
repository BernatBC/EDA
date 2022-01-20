#include "Player.hh"
#include <list>
#include <set>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene002


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
   typedef vector<vector<Cell>> map_cells;

   map_cells terrain;

    //Generates a map with the basic data
   void Get_map() {
     terrain = map_cells(cols(), vector<Cell>(rows()));
     for (int i = 0; i < rows(); ++i) {
       for (int j = 0; j < cols(); ++j) {
         terrain[i][j] = cell(i, j);
       }
     }
   }

   //Returns the positoin of the nearest city/path
   Pos bfs(Pos p) {
     list<Pos> to_visit;
     set<Pos> visited;
     to_visit.push_back(p);
     while (!to_visit.empty()) {
       Pos t = to_visit.front();
       to_visit.pop_front();
       if (visited.find(t) == visited.end()) {
         //If found, returns the posiotion of the nearest city wich is not mine
         if (p != t) {
           Cell cell_to_check = cell(t);
           if (terrain[t.i][t.j].type == CITY and city_owner(cell_to_check.city_id) != me()) return t;
           if (terrain[t.i][t.j].type == PATH and path_owner(cell_to_check.path_id) != me()) return t;
         }
         //If grass adds adjacent postions to check
         if (terrain[t.i][t.j].type == GRASS) {
           Pos c;
           c.i = t.i + 1;
           c.j = t.j;
           if (terrain[c.i][c.j].type != WALL) to_visit.push_back(c);
           c.i = t.i - 1;
           c.j = t.j;
           if (terrain[c.i][c.j].type != WALL) to_visit.push_back(c);
           c.i = t.i;
           c.j = t.j + 1;
           if (terrain[c.i][c.j].type != WALL) to_visit.push_back(c);
           c.i = t.i;
           c.j = t.j - 1;
           if (terrain[c.i][c.j].type != WALL) to_visit.push_back(c);
           visited.insert(t);
         }
       }
     }
     return p;
   }

   //Moves the player towards the nearest path/city
   void Go_closest(Pos pos, int id) {
     cerr << "pos: " << pos.i << " " << pos.j << endl;
     Pos nearest = bfs(pos);
     cerr << "nearest: " << nearest.i << " " << nearest.j << endl;
     if (nearest.i > pos.i) move(id, BOTTOM);
     else if (nearest.i < pos.i) move(id, TOP);
     else if (nearest.j > pos.j) move(id, RIGHT);
     else if (nearest.j < pos.j) move(id, LEFT);
     else move(id, NONE);
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //The first round generates a map
    if (round() == 0) Get_map();
    //Go to the closest city/path
    vector<int> units = my_units(me());
    for (int i = 0; i < units.size(); ++i) {
      Unit u = unit(units[i]);
      Go_closest(u.pos, units[i]);
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
