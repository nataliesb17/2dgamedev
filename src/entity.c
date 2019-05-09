#include <stdlib.h>
#include <string.h>
#include "entity.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"

typedef struct {
	Entity *entity;
	Uint32 *maxEntities;
}EntityManager;

//make EntityManager static (there can only be one, and it sits running as its own instance.
static EntityManager entityManager = { 0 };

//Destroy Entity Manager
void entity_manager_close() {
	//iterate all entities
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		//Destroy if there
		destroyEntity(&entityManager.entity[i]); //kill the MEMORY address
	}
	if (entityManager.entity) { //If there's a list of entities, kill it!
		free(entityManager.entity);
	}	entityManager.maxEntities = 0;
	entityManager.entity = NULL;
}

void entityManagerInit(Uint32 entity_limit) {
	//if max entity value is not present
	if (!entity_limit) {
		slog("cant have zero entities silly");
		return;
	}
	//Else, allocate memory based on max entities value
	entityManager.entity = (Entity*)malloc(sizeof(Entity)*entity_limit); //malloc is memory allocation, memset is using memory
	if (!entityManager.entity) {
		slog("can't allocate the entities", entity_limit);
	}

	entityManager.maxEntities = entity_limit;

	//Set the memory for manipulation
	memset(entityManager.entity, 0, sizeof(Entity)*entity_limit);

	//When exiting the game, make sure to destroy the entity Manager
	atexit(entity_manager_close);
}
/* Entity Manager
*@brief - manages entities
*@parameter - entity_limit
*@return - nothing
*/

Entity*ent_new() {
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		//find empty slot in list to use
		if (entityManager.entity[i].inUse) {
			continue;
		}
		//Set in use flag and make entity.
		entityManager.entity[i].inUse = 1;
		slog("Entity is being used");
		entityManager.entity[i].scale.x = 1;
		entityManager.entity[i].scale.y = 1;
		return &entityManager.entity[i];
	}
	//if there are no empty entity slots
	slog("all of the slots are taken");
	return NULL;
}
/*New Entity Creator
*@brief - new entity creator
*@parameter - none
*@return - blank entity, null if it doesn't work
*/

void destroyEntity(Entity*entity) {
	if (!entity)
	{
		return;
	}
	if (entity->sprite != NULL);
	{
		gf2d_sprite_free(entity->sprite);
	}
	memset(entity, 0, sizeof(Entity));
}
/* Destroy Entity
*@brief - destroys the entity created
*@parameter - entity
*@return - nothing
*/

void drawEntity(Entity*entity) {
	if (!entity) {
		return;
	}
	gf2d_sprite_draw(
		entity->sprite,           //sprite
		entity->position,         //position
		&entity->scale,           //scale
		NULL,                     //scaleCenterPoint
		NULL,                     //rotation
		NULL,                     //flip
		&entity->color,                     //colorShift
		entity->current_frame);   //frames
	if (&entity->hitbox)
		gf2d_shape_draw(entity->hitbox, gf2d_color(255,0,255,255), vector2d(0,0));
}
/* Draw Entity
*@brief - draws the entity
*@parameter - entity
*@return - nothing
*/

void update(Entity*entity) {
	if ((!entity) || (!entity->inUse))return;
	entity->current_frame += 0.35;
	if (entity->current_frame > entity->frame_num)entity->current_frame = 0;
	vector2d_add(entity->position, entity->position, entity->velocity);
	if (entity->update)entity->update(entity);
}
/* Update for Animation
*@brief - updates entity if animation is present
*@parameter - entity
*@return - nothing
*/
