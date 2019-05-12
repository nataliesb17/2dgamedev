#ifndef saveload_h
#define saveload_h

#include "entity.h"
#include "gf2d_vector.h"

typedef struct Save{
	Entity player;
	Vector2D position;
	Entity fireBall;
	Entity waterBall;
	Entity earthBall;
	Entity airBall;
}SaveFiles;

void save_file(SaveFiles *save, Entity *player);
void read_file(SaveFiles *save);
void load_file(SaveFiles *save, Entity *player);

#endif
