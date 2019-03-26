#ifndef Obstacles_h
#define Obstacles_h

#include "gf2d_sprite.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_shape.h"

Entity *newEarthObstacle(Vector2D position);
/**
* @brief this spawns a new obstacle
* @param position
* @return pointer for the obstacle
*/

Entity *newFireObstacle(Vector2D position);
/**
* @brief this spawns a new obstacle
* @param position
* @return pointer for the obstacle
*/

Entity *newWaterObstacle(Vector2D position);
/**
* @brief this spawns a new obstacle
* @param position
* @return pointer for the obstacle
*/


#endif