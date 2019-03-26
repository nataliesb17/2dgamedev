#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "gf2d_gui.h"
#include "obstacles.h"

void obs_update(Entity *self, Space *space);


Entity *newEarthObstacle(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new obstacle entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/col.png", 98, 32, 1); 
	entity->frame_num = 1;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->hitbox.id = 3;
	entity->hitbox.ability = 1;
	entity->hitbox.obstacle = 1;
	//entity->update = player_update;
	return entity;

}