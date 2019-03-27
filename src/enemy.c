#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "enemy.h"

//void enemy_update(Entity *enemy);
void x_enemy_update(Entity *enemy);
void y_enemy_update(Entity *enemy);


Entity *newStaticEnemy(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new enemy entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/glooRotated.png", 32, 32, 2); //this is the player sprite
	entity->frame_num = 2;
	//entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = enemy_update;
	return entity;

}
Entity *newYEnemy(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new enemy entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/glooRotated.png", 32, 32, 2); //this is the player sprite
	entity->frame_num = 2;
	//entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->update = y_enemy_update;
	entity->timer = 0;
	return entity;

}
Entity *newXEnemy(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new enemy entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/robot_scorpion.png", 50, 44, 1); //this is the player sprite
	entity->frame_num = 1;
	//entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->update = x_enemy_update;
	entity->timer = 0;
	return entity;

}

void y_enemy_update(Entity *enemy) {
	enemy->timer += 0.01f;
	if (enemy->timer >= 1.0f) {
		enemy->position.y += 1;
	}
	else {
		enemy->position.y -= 1;
	}
	if (enemy->timer >= 2.0f) {
		enemy->timer = 0;
	}
}
void x_enemy_update(Entity *enemy) {
	enemy->timer += 0.01f;
	if (enemy->timer >= 1.0f) {
		enemy->position.x += 1;
	}
	else {
		enemy->position.x -= 1;
	}
	if (enemy->timer >= 2.0f) {
		enemy->timer = 0;
	}
}
