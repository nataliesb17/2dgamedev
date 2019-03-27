#ifndef Enemy_h
#define Enemy_h

#include "gf2d_sprite.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_shape.h"
#include "Player.h"

Entity *newStaticEnemy(Vector2D position);
/**
* @brief this spawns a new enemy
* @param position
* @return pointer for the enemy
*/
Entity *newYEnemy(Vector2D position);
/**
* @brief this spawns a new enemy
* @param position
* @return pointer for the enemy
*/
Entity *newXEnemy(Vector2D position);
/**
* @brief this spawns a new enemy
* @param position
* @return pointer for the enemy
*/
Entity *newRandomEnemy(Vector2D position);
/**
* @brief this spawns a new enemy
* @param position
* @return pointer for the enemy
*/



#endif