#include "Numbers.h"
#include "ClockSprites.h"

void initClock(){
    REG_TM2D = -0x4000; // 0xFFFFC000, se inicia en este valor porque cuando pase un segundo el timer hace overflow
    REG_TM2CNT = TM_FREQ_1024 /*cada vez que el cpu completa 1024,aumenta un valor del timer*/ | TM_ENABLE; //hará overflow en 1 segundo
    REG_TM3CNT = TM_ENABLE | TM_CASCADE; //se habilita y se llena por cascada apenas el timer2 se llena
}

void initializeNumbersClock( OBJ_ATTR* buffer, Sprite *sprite, int posX){

    initializeSprite(sprite, buffer, posX, 70);
    assignAttributesSprite(sprite); //the sprite is loaded into memory
    loadSprite(NumbersTiles, NumbersTilesLen, NumbersPal, NumbersPalLen);

}

