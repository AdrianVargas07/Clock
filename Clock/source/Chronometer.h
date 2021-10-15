#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#ifndef CHRONOMETER
#define CHRONOMETER

#define TIME_OVERFLOW -1


void chrometer(OBJ_ATTR* buffer){
    u32 sec = TIME_OVERFLOW;
    u32 secTemp = TIME_OVERFLOW;
    u32 time = TIME_OVERFLOW;
    u32 start = TIME_OVERFLOW;


    REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D |  DCNT_BG0 | DCNT_BG1 | DCNT_MODE0;

    oam_init(buffer, 128); //se limpia la memoria

    Sprite spriteSecondsUnits;
    Sprite spriteSecondsTens;
    Sprite spriteMinutesUnits;
    Sprite spriteMinutesTens;
    Sprite spriteHoursUnits;
    Sprite spriteHoursTens;
    Sprite spriteSecondsPoints;
    Sprite spriteMinutesPoints;

    initializeNumbersClock(&buffer[0], &spriteSecondsUnits, 170);
    initializeNumbersClock(&buffer[1], &spriteSecondsTens, 150);
    initializeNumbersClock(&buffer[2], &spriteSecondsPoints, 135 );
    initializeNumbersClock(&buffer[3], &spriteMinutesUnits, 120);
    initializeNumbersClock(&buffer[4], &spriteMinutesTens, 100);
    initializeNumbersClock(&buffer[5], &spriteMinutesPoints, 85);
    initializeNumbersClock(&buffer[6], &spriteHoursUnits, 70);
    initializeNumbersClock(&buffer[7], &spriteHoursTens, 50);

    initClock();
    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));  

    char option[93] = {};
    snprintf(option, 93, "#{P:65,20} Chronometer \t\t#{P:10,125} <- Back: Press A \t\t#{P:10,130} Start, Stop Press B     ");
    tte_write(option);
    int corriendo = 0;
    int back = 0;
    
    while(!back){
        vid_vsync(); //sincronizar frames   
        
        while(!back){
            //marca el aumento en el tiempo
            time = REG_TM3D - start;
            if(corriendo == 0){
                secTemp = 0;
                sec = 0;
            }
            else if (corriendo == 1){
                secTemp = time;
            }
            else
            {
            }        

            if(secTemp != sec){ //cuando el tiempo incrementó

                //para probar actualizacion
                sec = time; //se actualiza el tiempo

                // segundos
                tickSpriteAnimation(&spriteSecondsUnits, (sec%60) % 10);
                tickSpriteAnimation(&spriteSecondsTens,  (sec/10) % 6  );

                points(&spriteSecondsPoints); //separacion entre minutos y segundos
                
                //minutos
                tickSpriteAnimation(&spriteMinutesUnits, ( (sec%3600)/60 ) % 10);            
                tickSpriteAnimation(&spriteMinutesTens,  (sec/600) % 6  );

                points(&spriteMinutesPoints); //separacion entre minutos y horas

                //horas
                tickSpriteAnimation(&spriteHoursUnits, (sec/3600) % 10);
                tickSpriteAnimation(&spriteHoursTens,  (sec/36000) % 6  ); 
            }

            key_poll();
            if(key_hit(KEY_B)){
                if(corriendo == 0){
                    corriendo = 1;
                    start = REG_TM3D;
                }
                else if(corriendo == 1)
                {
                    corriendo = 2;
                }
                else
                {
                    corriendo = 0;
                    //vuelve la cuenta a cero - limpia los valores
                    tickSpriteAnimation(&spriteSecondsUnits, 0);
                    tickSpriteAnimation(&spriteSecondsTens, 0);
                    tickSpriteAnimation(&spriteSecondsPoints, 0);
                    tickSpriteAnimation(&spriteMinutesUnits, 0);
                    tickSpriteAnimation(&spriteMinutesTens, 0);
                    tickSpriteAnimation(&spriteMinutesPoints, 0);
                    tickSpriteAnimation(&spriteHoursUnits, 0);
                    tickSpriteAnimation(&spriteHoursTens, 0);
                }
                
            }
            if(key_hit(KEY_A)){
                char option2[100] = {};
                snprintf(option2, 100, "#{P:85,20} Clock        \t\t\t#{P:10,125} Alarm->Press A     \t\t#{P:10,130} Chronometer->Press B" );
        tte_write(option2);
                back = 1;
            }

            oam_copy(oam_mem, buffer, 8 );
        }


        key_poll();
        if(key_hit(KEY_B)){
            //inicia o termina la cuenta
            
            
        }       
    }
}

#endif