#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "gf2d_shape.h"

void player_update(Entity *self);
void bodyTouch(struct Body_s *self, List *collision) {
	slog("what");
}

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

	entity->sprite = gf2d_sprite_load_all("images/player_sheet.png", 50, 50, 5); //this is the player sprite
	entity->frame_num = 5;
	entity->update = player_update;
	entity->hitbox = (&entity->hitbox, gf2d_shape_rect(position.x, position.y, 20, 20));
	gf2d_body_set(&entity->rigidBody, "body", 0, 1, 1, 3, position,vector2d(0,0),1,0,0,&entity->hitbox,NULL,bodyTouch);
	
	gf2d_body_set(
		&entity->rigidBody,
		"body",
		1,
		0,
		0,
		0,
		vector2d(256, 256),
		vector2d(2.3, 4.4),
		10,
		1,
		1,  //elasticity
		&entity->hitbox,
		NULL,
		NULL);
	gf2d_space_add_body(&entity->hitbox, &entity->rigidBody);
	for (i = 1; i < 100; i++)
	{
		gf2d_body_set(
			&entity->rigidBody,
			"body",
			1,
			0,
			0,
			0,
			vector2d(256 + 128, 256 + 128),
			vector2d(2.5 * gf2d_crandom(), 3 * gf2d_crandom()),
			10,
			1,
			1,  //elasticity
			&entity->hitbox,
			NULL,
			NULL);
		gf2d_space_add_body(&entity->hitbox, &entity->rigidBody);
	}

	return entity;

}

void player_update(Entity *self) {
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])self->position.y -= 1;
	if (keys[SDL_SCANCODE_A])self->position.x -= 1;
	if (keys[SDL_SCANCODE_S])self->position.y += 1;
	if (keys[SDL_SCANCODE_D])self->position.x += 1;

	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;

}









