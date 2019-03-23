#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"

void player_update(Entity *self);


Entity *newPlayer(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/player_sheet.png", 64, 64, 5); //this is the player sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	//entity->update = player_update;
	return entity;

}



void player_update(Entity *self, Space *space) {
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);

	vector2d_add(self->position, self->position, self->velocity);

	if (keys[SDL_SCANCODE_W])self->velocity.y -= .75;
	if (keys[SDL_SCANCODE_A])self->velocity.x -= .75;
	if (keys[SDL_SCANCODE_S])self->velocity.y += .75;
	if (keys[SDL_SCANCODE_D])self->velocity.x += .75;

	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;

	gf2d_shape_draw(self->hitbox, gf2d_color(1, 0, 0, 1),vector2d(0,0));

	Collision staticHit = gf2d_space_shape_test(space, self->hitbox);
	if (staticHit.collided >= 1) {
		slog("collision detected");
		self->velocity = vector2d(0, 0); //stops movement, but altogether
	}
	else {
		self->velocity = vector2d(0, .75);
	}


}









