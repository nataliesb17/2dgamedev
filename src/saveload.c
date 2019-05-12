#include "saveload.h"
#include "Player.h"
#include "projectiles.h"
#include <stdio.h>

void save_file(SaveFiles *saveFile, Entity *player, Entity *fireBall) {

	saveFile->position.x = player->position.x;
	saveFile->position.y = player->position.y;
	saveFile->player.color = player->color;

	saveFile->fireBall.position.x = fireBall->position.x;
	saveFile->fireBall.position.y = fireBall->position.y;

	FILE *fSave = fopen("save/saveFile.gameSave", "wb");
	fwrite(&(*saveFile), sizeof(struct Save), 1, fSave);
	fclose(fSave);
}

void read_file(SaveFiles *saveFile) {
	FILE *fSave = fopen("save/saveFile.gameSave", "rb");
	fread(&(*saveFile), sizeof(struct Save), 1, fSave);
	fclose(fSave);
}


void load_file(SaveFiles*saveFile, Entity *player, Entity *fireBall) {
	FILE *fSave = fopen("save/saveFile.gameSave", "rb");
	fread(&(*saveFile), sizeof(struct Save), 1, fSave);
	fclose(fSave);

	player->position.x = saveFile->position.x;
	player->position.y = saveFile->position.y;
	player->color = saveFile->player.color;

	fireBall->position.x = saveFile->fireBall.position.x;
	fireBall->position.y = saveFile->fireBall.position.y;

}
