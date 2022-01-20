#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME LeBene000


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
/*
   //Generates a map with the basic data
   void Get_map() {
     //Sets each cell to grass
     Cell cell_grass(GRASS, -1, -1, -1, 0, false);
     terrain = map_cells(rows(), vector<Cell>(cols(), cell_grass));
     //Sets cities to the map
     for (int i = 0; i < nb_cities(); ++i) {
       City c = city(i);
       Cell cell_city(CITY, -1, -1, -1, 0, false);
       for (int j = 0; j < c.size(); ++j) {
         terrain[c[j].j][c[j].i] = cell_city;
         cerr << "position:" << c[j].j << " " << c[j].i << endl;
       }
     }
   }*/

   // Moves all units of the player.
   void move_units(int id) {
 		  // We process the units in random order.
 		  Unit u = unit(id);
 		  // With probability 1/4, we move at random.
 		  if (random(0, 3)) move(id, Dir(random(0, DIR_SIZE - 1)));

 		  else if (u.damage > 0) { // If the unit is currently infected:
 			  bool moved = false;
 			  Pos p0 = u.pos;
 			  for (int d = 0; d < 4 and not moved; ++d) {
 				  Pos p1 = p0 + Dir(d);
 				  if (pos_ok(p1)) {
 						Cell c1 = cell(p1);
 						if (c1.mask) { // If there's a mask nearby, go there.
 							moved = true;
 							move(id, Dir(d));
 						}
 					}
 			  }
 			  if (not moved) move(id, NONE);
 		  }
 		  else {
 			  // Otherwise, do a bunch of (probably) stupid things.
 			  // It's just to show that there are many possibilities.
 			  if (u.immune) move(id, LEFT);
 			  else if (cell(u.pos).type == CITY) {
 					Cell c = cell(u.pos);
 					if (city_owner(c.city_id) != me()) move(id, TOP);
 					else if (c.virus >= 3) move(id, RIGHT);
 					else move(id, BOTTOM);
 				}
 				else {
 					if (cell(3, 4).type == WALL) move(id, NONE);
 					else if (u.health < 30) move(id, BOTTOM);
 					else if (cell(u.pos + TOP).unit_id != -1) {
 						Unit u1 = unit(cell(u.pos + TOP).unit_id);
 						if (u1.player == me()) move(id, RIGHT);
 						else if (u1.turns >= 15) move(id, NONE);
 						else if (u1.mask) move(id, LEFT);
 						else move(id, TOP);
 					}
 					else if (random(0, 1)) move(id, Dir(random(0, 2)));
 					// You can also use cerr to debug.
 					// else cerr << u.pos.i << " " << u.pos.j << endl;
 				}
 		  }
 	  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //The first round generates a map
    //if (round() == 1) Get_map();
    vector<int> units = my_units(me());
    for (int i = 0; i < units.size(); ++i) {
      move_units(units[i]);
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
