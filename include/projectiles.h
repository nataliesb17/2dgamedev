#ifndef projectiles_h
#define projectiles_h

#include "gf2d_sprite.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_shape.h"

Entity *newFireProjectile(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newWaterProjectile(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newAirProjectile(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *newEarthProjectile(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/



#endif