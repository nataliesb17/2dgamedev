#include "player.h"
#include "simple_logger.h"
#include "entity.h"

void player_update(Entity *self);

Entity *newPlayer(Vector2D position)
{
	Entity *entity = NULL;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16); //this is the player sprite
	entity->frame_num = 48;
	entity->update = player_update;
	return entity;

}

void player_update(Entity *self) {
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])self->position.y -= 1;
	if (keys[SDL_SCANCODE_A])self->position.x -= 1;
	if (keys[SDL_SCANCODE_S])self->position.y += 1;
	if (keys[SDL_SCANCODE_D])self->position.x += 1;
}






