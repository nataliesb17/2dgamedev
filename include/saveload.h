#ifndef saveload_h
#define saveload_h

#include "entity.h"
#include "gf2d_vector.h"

typedef struct Save{
	Entity player;
	Vector2D position;
}SaveFiles;

void Save_file(SaveFiles *save);
void Load_file(SaveFiles *save);

#endif