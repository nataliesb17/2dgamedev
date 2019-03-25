#include "projectiles.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "player.h"

void projectile_update(Entity *self, Entity *player);


Entity *newFireProjectile(Vector2D position) //fire element
{
	Entity *entity = NULL;
	int i;
	int elementalAbility = 3;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new projectile entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/fire_ball.png", 32, 32, 1); //this is the projectile sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}

Entity *newWaterProjectile(Vector2D position) //water element
{
	Entity *entity = NULL;
	int i;
	int elementalAbility = 2;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new projectile entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/water_ball.png", 32, 32, 1); //this is the projectile sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}

Entity *newAirProjectile(Vector2D position) 
{
	Entity *entity = NULL;
	int i;
	int elementalAbility = 1;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new projectile entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/air_ball.png", 32, 32, 1); //this is the projectile sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}

Entity *newEarthProjectile(Vector2D position) 
{
	Entity *entity = NULL;
	int i;
	int elementalAbility = 4;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new projectile entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/earth_ball.png", 32, 32, 1); //this is the projectile sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}



void projectile_update(Entity *projectile, Space *entity) {
	Collision bodyHit = gf2d_space_shape_test(entity, projectile->hitbox);
	if (bodyHit.collided >= 1) {
		slog("picked detected");
	}
}