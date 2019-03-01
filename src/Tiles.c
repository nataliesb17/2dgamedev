#include "tiles.h"
#include "simple_logger.h"
#include "entity.h"
#include "gf2d_graphics.h"
#include "player.h"

void tile_loop(Entity *tile);

int *tile_num;
Entity *tiles;
int x;
int y;

Entity *newTile(Vector2D position)
{
	Entity *entity = NULL;
	entity = ent_new();
	vector2d_copy(entity->position, position);
	entity->sprite = gf2d_sprite_load_all("images/test_tile.png", 32, 32, NULL);
	return entity;
}

void tile_loop(Entity *tile) {
	tile_num = 0;
	while (tile_num < 20) {
		x += 10;
		y += 10;
		tiles = newPlayer(vector2d(x, y), tiles);
		drawEntity(tiles);
		tile_num += 1;
	}
}