#include "Player.hh"
#include <list>
#include <set>
#include <map>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene020


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
   vector<int> units;

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
   Dir bfs(Pos p) {
     list<Pos> to_visit;
     set<Pos> visited;
     map<Pos,Dir>direction;
     to_visit.push_back(p);
     int dist = 0;
     int dist_cp = 0;
     Dir dir_cp = NONE;
     bool first = true;
     while (!to_visit.empty()) {
       Pos t = to_visit.front();
       to_visit.pop_front();
       if (visited.find(t) == visited.end()) {
         //Checks if there's an enemy
         Cell cell_u = cell(p);
         if (cell_u.unit_id != -1 and not Unit_is_mine(cell_u.unit_id)) return direction[t];
         //If found, returns the posiotion of the nearest city wich is not mine
         if (p != t) {
           Cell cell_to_check = cell(t);
           if (terrain[t.i][t.j].type == CITY and city_owner(cell_to_check.city_id) != me() and dir_cp == NONE) {
             dist_cp = dist;
             dir_cp = direction[t];
             return direction[t];
           }
           if (terrain[t.i][t.j].type == PATH and path_owner(cell_to_check.path_id) != me() and dir_cp == NONE) {
             dist_cp = dist;
             dir_cp = direction[t];
             return direction[t];
           }
         }
         //If grass adds adjacent postions to check
         if (terrain[t.i][t.j].type != WALL) {
           Pos c;
           c.i = t.i + 1;
           c.j = t.j;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             if (first) direction[c] = BOTTOM;
             else direction[c] = direction[t];
           }
           c.i = t.i - 1;
           c.j = t.j;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             if (first) direction[c] = TOP;
             else direction[c] = direction[t];
           }
           c.i = t.i;
           c.j = t.j + 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             if (first) direction[c] = RIGHT;
             else direction[c] = direction[t];
           }
           c.i = t.i;
           c.j = t.j - 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             if (first) direction[c] = LEFT;
             else direction[c] = direction[t];
           }
         }
         visited.insert(t);
         first = false;
         ++dist;
       }
     }
     return Dir(random(0, DIR_SIZE - 1));
   }

   //Returns if a unit is mine
   bool Unit_is_mine(int id) {
     for (int i = 0; i < units.size(); ++i) {
       if (id == units[i]) return true;
     }
     return false;
   }

   bool moved_to_enemy(Unit u) {
    Pos p = u.pos;
    Cell c;
    //Bottom
    p.i = p.i + 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      move(u.id, BOTTOM);
      return true;
    }
    //Top
    p.i = u.pos.i - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      move(u.id, TOP);
      return true;
    }
    //Right
    p.i = u.pos.i;
    p.j = u.pos.j + 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      move(u.id, RIGHT);
      return true;
    }
    //Left
    p.j = u.pos.j - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      move(u.id, LEFT);
      return true;
    }
     return false;
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //The first round generates a map
    if (round() == 0) Get_map();
    units = my_units(me());
    for (int i = 0; i < units.size(); ++i) {
      Unit u = unit(units[i]);
      //Check if can attack
      if (not moved_to_enemy(u)) {
        //Go to the closest city/path
        move(units[i], bfs(u.pos));
      }
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
