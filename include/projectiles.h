#ifndef pickups_h
#define pickups_h

#include "gf2d_sprite.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_shape.h"

Entity *newFirepickup(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newWaterpickup(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newAirpickup(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newEarthpickup(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/



#endif