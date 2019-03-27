#include "saveload.h"
#include <stdio.h>

void save_file(SaveFiles*saveFile,Vector2D position) {
	FILE *fSave = fopen("save/saveFile.gameSave", "wb");
	fwrite(&(*saveFile), sizeof(struct Save), 1, fSave);
	fclose(saveFile);
}
void load_file(SaveFiles*saveFile,Vector2D position) {
	FILE *fSave = fopen("save/saveFile.gameSave", "rb");
	fread(&(*saveFile), sizeof(struct Save), 1, fSave); 
	fclose(saveFile);
}