#include "Player.hh"
#include <list>
#include <set>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene001


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
   /*
   //Generates a map with the basic data
   void Get_map() {
     //Sets each cell to grass
     Cell cell_grass(GRASS, -1, -1, -1, 0, false);
     terrain = map_cells(rows(), vector<Cell>(cols(), cell_grass));
     //Sets cities to the map
     for (int a1 = 0; a1 < nb_cities(); ++a1) {
       cerr << a1 << endl;
       City cit = city(a1);
       cerr << "ok" << endl;
       Cell cell_city(CITY, -1, -1, -1, 0, false);
       for (int a2 = 0; a2 < cit.size(); ++a2) {
         terrain[cit[a2].j][cit[a2].i] = cell_city;
       }
     }
     //Sets paths to the map
     for (int a1 = 0; a1 < nb_paths(); ++a1) {
       Path p = path(a1);
       Cell cell_path(PATH, -1, -1, -1, 0, false);
       for (int a2 = 0; a2 < p.second.size(); ++a2) {
         terrain[p.second[a2].j][p.second[a2].i] = cell_path;
       }
     }
   }*/
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
         //If found, returns the posiotion
         if (p != t and (terrain[t.i][t.j].type == CITY or terrain[t.i][t.j].type == PATH)) return t;
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
