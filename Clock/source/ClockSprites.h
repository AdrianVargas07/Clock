#ifndef CLOCKSPRITES
#define CLOCKSPRITES

#include "tonc.h"

typedef struct{

	OBJ_ATTR *spriteAttribs;
	int firstAnimCycleFrame;
	int animFrame;
	int posX;
	int posY;

}Sprite;

void initializeSprite(Sprite* sprite, OBJ_ATTR* attribs, int x, int y) {

	sprite->spriteAttribs = attribs;
	sprite->firstAnimCycleFrame = 0;
	sprite->animFrame = 0;
	sprite->posX = x;
	sprite->posY = y;
}

void loadSprite(const unsigned int* tiles, const unsigned int tilesLen, const unsigned int*  pal, const unsigned int  panLen){

	memcpy(&tile_mem[4][0], tiles, tilesLen); // copy the sprite into memory (sprite definition)
	memcpy(pal_obj_mem, pal, panLen);		  // copy the part of the palette into memory
}

void assignAttributesSprite(Sprite* sprite){

	sprite->spriteAttribs->attr0 = ATTR0_8BPP | ATTR0_SQUARE;
	sprite->spriteAttribs->attr1 = ATTR1_SIZE_16;
	obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY);

}

void tickSpriteAnimation(Sprite* sprite, int n){

     OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;

    sprite->animFrame++;
	sprite->firstAnimCycleFrame = 8 * n;
 	sprite->animFrame = (sprite->animFrame) % 1;
 	spriteAttribs->attr2= ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame*8), 0, 0);

}

void points(Sprite* sprite){

	OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;
 	spriteAttribs->attr2= ATTR2_BUILD(80, 0, 0);

}

#endif