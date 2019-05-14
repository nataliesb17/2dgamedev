#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "gf2d_gui.h"
#include "obstacles.h"

void fireObstacle_update(Entity *obstacle);
void waterObstacle_update(Entity *obstacle);

Entity *newEarthObstacle(Vector2D position)
{
	Entity *entity = NULL;
	int i;
	Space *space = NULL;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new obstacle entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/col.png", 98, 32, 1); 
	entity->frame_num = 1;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 98, 32);
	entity->hitbox.id = 3;
	entity->hitbox.ability = 1;
	entity->hitbox.obstacle = 1;
	entity->rigidBody.shape = &entity->hitbox;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}
Entity *newFireObstacle(Vector2D position)
{
	Entity *entity = NULL;
	int i;
	Space *space = NULL;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new obstacle entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/leaff.png", 100, 87, 1);
	entity->frame_num = 1;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 100, 87);
	entity->hitbox.id = 3;
	entity->hitbox.ability = 3;
	entity->hitbox.obstacle = 3;
	entity->rigidBody.shape = &entity->hitbox;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}
Entity *newWaterObstacle(Vector2D position)
{
	Entity *entity = NULL;
	int i;
	Space *space = NULL;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new obstacle entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/fire.png", 32, 50, 1);
	entity->frame_num = 1;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 32, 50);
	entity->hitbox.id = 3;
	entity->hitbox.ability = 4;
	entity->hitbox.obstacle = 4;
	entity->rigidBody.shape = &entity->hitbox;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->update = player_update;
	return entity;

}
Entity *newDoor(Vector2D position) {
	Entity *entity = NULL;
	int i;
	Space *space = NULL;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new obstacle entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/door.png", 32, 32, 1);
	entity->frame_num = 1;
	entity->hitbox.id = 5;
	entity->hitbox.ability = 5;
	entity->rigidBody.shape = &entity->hitbox;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 32, 32);
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	return entity;
}
