#ifndef Entity_h
#define Entity_h
#include "gf2d_vector.h"
#include "gf2d_sprite.h"
#include "gf2d_shape.h"
#include "collision.h"
#include "gf2d_particles.h"

typedef struct entities {

	int inUse;

	Vector2D position;
	Vector2D scale;
	Vector2D velocity;
	Sprite *sprite;
	Shape hitbox; 
	Body rigidBody;
	Space *space;
	Vector4D color;

	float timer;
	float current_frame;
	int frame_num;
	int onGround;
	int ability;

	void(*update)(struct entities * entity);

}Entity;

void entityManagerInit(Uint32 entity_limit);
/* Entity Manager
*@brief - manages entities
*@parameter - entity_limit
*@return - nothing
*/


Entity*ent_new();
/*New Entity Creator
*@brief - new entity creator
*@parameter - none
*@return - blank entity, null if it doesn't work
*/

void destroyEntity(Entity*entity);
/* Destroy Entity
*@brief - destroys the entity created
*@parameter - entity
*@return - nothing
*/

void drawEntity(Entity*entity);
/* Draw Entity
*@brief - draws the entity
*@parameter - entity
*@return - nothing
*/

void drawAllEntities();

void update(Entity *ent);
/* Update for Animation
*@brief - updates entity if animation is present
*@parameter - entity
*@return - nothing
*/

//end of code

#endif