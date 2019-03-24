#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "enemy.h"

void enemy_update(Entity *self);

Entity *newEnemy(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/glooRotated.png", 32, 32, 2); //this is the player sprite
	entity->frame_num = 2;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}