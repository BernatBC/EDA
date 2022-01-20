#include "Player.hh"
#include <list>
#include <set>
#include <map>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene039


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
     map<Pos,int>distance;
     map<Dir,int> direction_count;
     direction_count[TOP] = 0;
     direction_count[BOTTOM] = 0;
     direction_count[LEFT] = 0;
     direction_count[RIGHT] = 0;
     distance[p] = 0;
     int min_dist = 0;
     to_visit.push_back(p);
     bool first = true;
     while (!to_visit.empty()) {
       Pos t = to_visit.front();
       to_visit.pop_front();
       if (visited.find(t) == visited.end()) {
         //Looks for the best direction
         if (min_dist != 0 and min_dist < distance[t]) {
           if (direction_count[BOTTOM] >= direction_count[TOP]) {
             if (direction_count[RIGHT] >= direction_count[LEFT]) {
               if (direction_count[BOTTOM] >= direction_count[RIGHT]) return BOTTOM;
               else return RIGHT;
             }
             if (direction_count[BOTTOM] >= direction_count[LEFT]) return BOTTOM;
             else return LEFT;
           }
           else {
             if (direction_count[RIGHT] >= direction_count[LEFT]) {
               if (direction_count[TOP] >= direction_count[RIGHT]) return TOP;
               else return RIGHT;
             }
             if (direction_count[TOP] >= direction_count[LEFT]) return TOP;
             else return LEFT;
           }
         }
         //If found, returns the position of the nearest city which is not mine
         if (p != t) {
           Cell cell_to_check = cell(t);
           if (cell_to_check.unit_id != -1 and not Unit_is_mine(cell_to_check.unit_id)) direction_count[direction[t]] += 1;
           if ((terrain[t.i][t.j].type == PATH and path_owner(cell_to_check.path_id) != me()) or (terrain[t.i][t.j].type == CITY and city_owner(cell_to_check.city_id) != me())) {
             min_dist = distance[t];
             direction_count[direction[t]] += 4;
           }
         }
         //If grass adds adjacent positions to check
         if (terrain[t.i][t.j].type != WALL) {
           Pos c;
           c.i = t.i + 1;
           c.j = t.j;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             distance[c] = distance[t] + 1;
             if (first) direction[c] = BOTTOM;
             else direction[c] = direction[t];
           }
           c.i = t.i - 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             distance[c] = distance[t] + 1;
             if (first) direction[c] = TOP;
             else direction[c] = direction[t];
           }
           c.i = t.i;
           c.j = t.j + 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             distance[c] = distance[t] + 1;
             if (first) direction[c] = RIGHT;
             else direction[c] = direction[t];
           }
           c.j = t.j - 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
             distance[c] = distance[t] + 1;
             if (first) direction[c] = LEFT;
             else direction[c] = direction[t];
           }
         }
         visited.insert(t);
         first = false;
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
    int p_bottom = 0;
    int p_top = 0;
    int p_left = 0;
    int p_right = 0;
    //Bottom
    p.i = p.i + 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_bottom;
      if (c.city_id != -1) {
        ++p_bottom;
        if (city_owner(c.city_id) != me()) ++p_bottom;
      }
      if (c.path_id != -1) {
        ++p_bottom;
        if (path_owner(c.path_id) != me()) ++p_bottom;
      }
    }
    //Top
    p.i = u.pos.i - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_top;
      if (c.city_id != -1) {
        ++p_top;
        if (city_owner(c.city_id) != me()) ++p_top;
      }
      if (c.path_id != -1) {
        ++p_top;
        if (path_owner(c.path_id) != me()) ++p_top;
      }
    }
    //Right
    p.i = u.pos.i;
    p.j = u.pos.j + 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_right;
      if (c.city_id != -1) {
        ++p_right;
        if (city_owner(c.city_id) != me()) ++p_right;
      }
      if (c.path_id != -1) {
        ++p_right;
        if (path_owner(c.path_id) != me()) ++p_right;
      }
    }
    //Left
    p.j = u.pos.j - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_left;
      if (c.city_id != -1) {
        ++p_left;
        if (city_owner(c.city_id) != me()) ++p_left;
      }
      if (c.path_id != -1) {
        ++p_left;
        if (path_owner(c.path_id) != me()) ++p_left;
      }
    }
    //In case there's no enemy return false
    if (p_bottom + p_top + p_left + p_right == 0) return false;
    //If there's an ememy or more, look for the best cell
    if (p_bottom >= p_top) {
      if (p_right >= p_left) {
        if (p_bottom >= p_right) move(u.id, BOTTOM);
        else move(u.id, RIGHT);
      }
      if (p_bottom >= p_left) move(u.id, BOTTOM);
      else move(u.id, LEFT);
    }
    else {
      if (p_right >= p_left) {
        if (p_top >= p_right) move(u.id, TOP);
        else move(u.id, RIGHT);
      }
      if (p_top >= p_left) move(u.id, TOP);
      else move(u.id, LEFT);
    }
    return true;
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
