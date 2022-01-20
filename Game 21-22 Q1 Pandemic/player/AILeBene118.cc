#include "Player.hh"
#include <list>
#include <set>
#include <map>
#include <cmath>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene118


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
   typedef vector<vector<int>> Mat;

   //Matrix representing the map
   map_cells terrain;
   // mat[0][i]-> Each city contain an array of adjacent cities
   Mat cities;
   //Array of my units
   vector<int> units;
   //first->city.id, second->city.size
   map<int, int> cities_size;
   //first->path.id, second->path.size
   map<int, int> paths_size;
   //First.first->city1.id, first.second->city2.id, second->path.id
   map<pair<int,int>,int> path_id;

    //Generates a map with the basic data
   void Get_map() {
     terrain = map_cells(cols(), vector<Cell>(rows()));
     cities = Mat(nb_cities());
     //Initialize city size
     for (int i = 0; i < nb_cities(); ++i) cities_size[i] = 0;
     //Initialize path size
     for (int i = 0; i < nb_paths(); ++i) paths_size[i] = 0;
     //Get map
     for (int i = 0; i < rows(); ++i) {
       for (int j = 0; j < cols(); ++j) {
         terrain[i][j] = cell(i, j);
         //Add city size
         if (terrain[i][j].city_id != -1) cities_size[terrain[i][j].city_id]++;
         //Add path size
         if (terrain[i][j].path_id != -1) paths_size[terrain[i][j].path_id]++;
       }
     }
     //Get adjacent cities matrix
     for (int i = 0; i < nb_paths(); ++i) {
       Path p = path(i);
       cities[p.first.first].push_back(p.first.second);
       cities[p.first.second].push_back(p.first.first);
       path_id[make_pair(p.first.first, p.first.second)] = i;
       path_id[make_pair(p.first.second, p.first.first)] = i;
     }
   }

   //Returns the number of components I'll have if I conquer the city
   int compute_score(int city_id, int suposed_path_id) {
     set<int> cities_visited;
     set<int> cities_to_visit;
     cities_to_visit.insert(city_id);
     int n_cities = 1;
     int cities_points = 0;
     int path_points = 0;
     while (not cities_to_visit.empty()) {
       auto it = cities_to_visit.begin();
       int city_to_treat = *it;
       cities_visited.insert(city_to_treat);
       cities_to_visit.erase(it);
       //Iterate for each adjacent city
       for (int i = 1; i < cities[city_to_treat].size(); ++i) {
         Path p = path(path_id[make_pair(city_to_treat, cities[city_to_treat][i])]);
         //Check if I own the path
         if (path_owner(path_id[make_pair(city_to_treat, cities[city_to_treat][i])]) == me() or suposed_path_id == path_id[make_pair(city_to_treat, cities[city_to_treat][i])]) {
           //Add path points
           path_points += paths_size[path_id[make_pair(city_to_treat, cities[city_to_treat][i])]];
           //Check if the city has ever been treated
           if (cities_visited.find(cities[city_to_treat][i]) == cities_visited.end() and cities_to_visit.find(cities[city_to_treat][i]) == cities_to_visit.end()) {
             //Check if I own the city
             if (city_owner(cities[city_to_treat][i]) == me()) {
               cities_to_visit.insert(cities[city_to_treat][i]);
               cities_points += cities_size[cities[city_to_treat][i]];
               ++n_cities;
             }
           }
         }
       }
     }
     return pow(2,n_cities)*factor_connected_component() + cities_points + path_points;
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
           //Apply multipliers to go to the middle
           if (p.i > rows()/2 + 15) direction_count[TOP] *= 3;
           else if (p.i < rows()/2 - 15) direction_count[BOTTOM] *= 3;
           if (p.j > cols()/2 + 15) direction_count[LEFT] *= 3;
           else if (p.j < cols()/2 - 15) direction_count[RIGHT] *= 3;

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
           if (terrain[t.i][t.j].type == PATH and path_owner(cell_to_check.path_id) != me()) {
             min_dist = distance[t];
             Path p = path(cell_to_check.path_id);
             int city1 = p.first.first;
             int city2 = p.first.second;
             if (city_owner(city1) == me() and city_owner(city2) == me()) direction_count[direction[t]] += compute_score(city1, cell_to_check.path_id);
             else direction_count[direction[t]] += paths_size[cell_to_check.path_id];
           }
           else if (terrain[t.i][t.j].type == CITY and city_owner(cell_to_check.city_id) != me()) {
             min_dist = distance[t];
             direction_count[direction[t]] += compute_score(cell_to_check.city_id, -1);
           }
           if (round() <= 50 and cell_to_check.unit_id != -1 and not Unit_is_mine(cell_to_check.unit_id) and unit(cell_to_check.unit_id).health <= 25) return direction[t];
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

   //Simplified bfs when I run low on cpu
   Dir bfs_low_cpu(Pos p) {
     list<Pos> to_visit;
     set<Pos> visited;
     map<Pos,Dir>direction;
     to_visit.push_back(p);
     bool first = true;
     while (!to_visit.empty()) {
       Pos t = to_visit.front();
       to_visit.pop_front();
       if (visited.find(t) == visited.end()) {
         //If found, returns the position of the nearest city which is not mine
         if (p != t) {
           Cell cell_to_check = cell(t);
           if ((terrain[t.i][t.j].type == PATH and path_owner(cell_to_check.path_id) != me()) or (terrain[t.i][t.j].type == CITY and city_owner(cell_to_check.city_id) != me())) return direction[t];
         }
         //If grass adds adjacent positions to check
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
           c.j = t.j - 1;
           if (terrain[c.i][c.j].type != WALL) {
             to_visit.push_back(c);
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

   Dir moved_to_enemy(Unit u) {
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
      if (unit(c.unit_id).health <= 25) p_bottom += 5;
      if (c.city_id != -1) {
        ++p_bottom;
        if (city_owner(c.city_id) != me()) ++p_bottom;
      }
      if (c.path_id != -1) {
        ++p_bottom;
        if (path_owner(c.path_id) != me()) ++p_bottom;
      }
       if (unit(c.unit_id).damage > 0 ) p_bottom *= 2;
    }
    //Top
    p.i = u.pos.i - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_top;
      if (unit(c.unit_id).health <= 25) p_top += 5;
      if (c.city_id != -1) {
        ++p_top;
        if (city_owner(c.city_id) != me()) ++p_top;
      }
      if (c.path_id != -1) {
        ++p_top;
        if (path_owner(c.path_id) != me()) ++p_top;
      }
      if (unit(c.unit_id).damage > 0 ) p_top *= 2;
    }
    //Right
    p.i = u.pos.i;
    p.j = u.pos.j + 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_right;
      if (unit(c.unit_id).health <= 25) p_right += 5;
      if (c.city_id != -1) {
        ++p_right;
        if (city_owner(c.city_id) != me()) ++p_right;
      }
      if (c.path_id != -1) {
        ++p_right;
        if (path_owner(c.path_id) != me()) ++p_right;
      }
      if (unit(c.unit_id).damage > 0 ) p_right *= 2;
    }
    //Left
    p.j = u.pos.j - 1;
    c = cell(p);
    if (c.unit_id != -1 and not Unit_is_mine(c.unit_id)) {
      ++p_left;
      if (unit(c.unit_id).health <= 25) p_left += 5;
      if (c.city_id != -1) {
        ++p_left;
        if (city_owner(c.city_id) != me()) ++p_left;
      }
      if (c.path_id != -1) {
        ++p_left;
        if (path_owner(c.path_id) != me()) ++p_left;
      }
      if (unit(c.unit_id).damage > 0 ) p_left *= 2;
    }
    //In case there's no enemy return NONE
    if (p_bottom + p_top + p_left + p_right == 0) return NONE;
    //If there's an ememy or more, look for the best cell
    if (p_bottom >= p_top) {
      if (p_right >= p_left) {
        if (p_bottom >= p_right) return BOTTOM;
        else return RIGHT;
      }
      if (p_bottom >= p_left) return BOTTOM;
      else return LEFT;
    }
    else {
      if (p_right >= p_left) {
        if (p_top >= p_right) return TOP;
        else return RIGHT;
      }
      if (p_top >= p_left) return TOP;
      else return LEFT;
    }
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
      Dir d = moved_to_enemy(u);
      if (d == NONE) {
        //Get best direction
        if (status(me()) > 0.75) d = bfs_low_cpu(u.pos);
        else d = bfs(u.pos);
      }
      move(units[i], d);
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
