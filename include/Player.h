#ifndef Player_h
#define Player_h

#include "gf2d_sprite.h"
#include "entity.h"

Entity *newPlayer(Vector2D position);
/**
* @brief this spawns a new player
* @param position
* @return pointer for the player
*/

Entity *player_update(Entity *self);
/**
* @brief this updates the player's position
* @param self
* @return nothing
*/

void *player_set_position(Vector2D position);
/**
* @brief this sets the player position at spawn
* @param position
* @return coordinates of player location
*/

#endif