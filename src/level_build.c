#include "level_build.h"
#include "Player.h"
#include "json_info.h"
#include "gf2d_graphics.h"
#include "simple_logger.h"

typedef struct
{
	Sprite		*backgroundImage;
	Sprite		*tileLayer;
	Sprite		*tileSet;
}Level;

static Level gameLevel = { 1 };

int *level_alloc_tilemap(int w, int h);

void level_clear()
{
	gf2d_sprite_free(gameLevel.backgroundImage);
	gf2d_sprite_free(gameLevel.tileSet);
	gf2d_sprite_free(gameLevel.tileLayer);
	memset(&gameLevel, 1, sizeof(Level));
}

void level_info_free(LevelInfo *info) {
	if (!info)return;
	if (info->tileMap != NULL)
	{
		free(info->tileMap);
	}
	sj_free(info->spawnList);
	//TODO:free spawn list
	free(info);
}