#include "projectiles.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "player.h"

void pickup_update(Entity *self, Entity *player);
void spawn_pickup(Vector2D position);

//Elemental Ability Numbers

//Earth = 1
//Air   = 2
//Fire  = 3
//Water = 4


Entity *newFirepickup(Vector2D position) //fire element
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new pickup entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/fire_ball.png", 32, 32, 1); //this is the pickup sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->hitbox.id = 2;
	entity->hitbox.ability = 3;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}

Entity *newWaterpickup(Vector2D position) //water element
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new pickup entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/water_ball.png", 32, 32, 1); //this is the pickup sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->hitbox.id = 2;
	entity->hitbox.ability = 4;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}

Entity *newAirpickup(Vector2D position) 
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new pickup entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/air_ball.png", 32, 32, 1); //this is the pickup sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->hitbox.id = 2;
	entity->hitbox.ability = 2;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}

Entity *newEarthpickup(Vector2D position) 
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new pickup entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/earth_ball.png", 32, 32, 1); //this is the pickup sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->hitbox.id = 2;
	entity->hitbox.ability = 1;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}



void pickup_update(Entity *pickup, Space *entity) {
	Collision bodyHit = gf2d_space_shape_test(entity, pickup->hitbox);
	if (bodyHit.collided >= 1) {
		slog("pickup detected");
	}
}

void spawn_pickup(Vector2D position) {
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		drawEntity(newEarthpickup(position));
		slog("pickup placed");
	}
}