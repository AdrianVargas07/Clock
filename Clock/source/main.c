#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Clock.h"
#include "Chronometer.h"
#include "Alarm.h"

#define TIME_OVERFLOW -1
u32 sec = TIME_OVERFLOW;

OBJ_ATTR buffer[128];

int secondsUnits = -1;
int secondsTens  = 1; 
int minutesUnits = -1;
int minutesTens  = 1;
int hoursUnits   = -1;
int hoursTens    = 1;

int activeAlarm = 0;

int bit = 1; 

int main(){
    
    REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D |  DCNT_BG0 | DCNT_BG1 | DCNT_MODE0;

	oam_init(buffer, 128); // se inicializa memoria oam

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

    char option[81] = {}; //buffer para imprimir
    snprintf(option, 81, "#{P:85,20} Clock \t\t#{P:10,125} Alarm->Press A \t\t#{P:10,130} Chronometer->Press B" );
    tte_write(option);

    while(1){
        
        vid_vsync(); //sincronixar frames        

        if(REG_TM3D != sec){ //cuando el tiempo incrementó

            sec = REG_TM3D; //se actualiza el tiempo

            // segundos
            tickSpriteAnimation(&spriteSecondsUnits, (sec%60) % 10);

            tickSpriteAnimation(&spriteSecondsTens,  (sec/10) % 6  );
              
            //separacion entre minutos y segundos    
            points(&spriteSecondsPoints);           
            
            //minutos
            tickSpriteAnimation(&spriteMinutesUnits, ( (sec%3600)/60 ) % 10);            

            tickSpriteAnimation(&spriteMinutesTens,  (sec/600) % 6  );
           
           //separacion entre horas y minutos
            points(&spriteMinutesPoints); 

            //horas               

            //se debe controlar que las horas solo lleguen a 12
            // if(bit == 1) {                     

            tickSpriteAnimation(&spriteHoursUnits, (sec/3600) % 10);

            tickSpriteAnimation(&spriteHoursTens,  (sec/36000) % 6  ); 

            // if( ( (sec/3600) % 10 ) == 0 ) {
            //     bit = 0;
            // }             

            // }else{

            //     tickSpriteAnimation(&spriteHoursUnits, (sec/3600) % 3);

            //     //tickSpriteAnimation(&spriteHoursTens,  (sec/36000) % 2 ); 

            //     //  if( ( (sec/3600) % 3 ) == 0 && ( (sec/36000) % 10) == 1 ) 
            //     //      bit = 1;
            // }          
            
        }

        key_poll();
        
        //para entrar al modo alarma
        if(key_hit(KEY_A)){
            alarm(buffer, &activeAlarm);

            //para borrar el confired alarm!
            char option[31] = {}; //buffer para imprimir
            snprintf(option, 31, "#{P:50,90}                    " );
            tte_write(option);
        }
                          
        //para entrar a modo cronometro
        if(key_hit(KEY_B))
            chrometer(buffer);


        //si se activa la alarma se muestra un mensaje en la ventana reloj que indica la hora de la alarma
        if(activeAlarm){

            //se imprime en la pantalla del reloj la hora que se ha configurado en la alarma
            char option[31] = {}; //buffer para imprimir
            snprintf(option, 31, "#{P:40,50} Alarm time: %01d%01d:%01d%01d", minutesTensAlarm, minutesUnitsAlarm, secondsTensAlarm, secondsUnitsAlarm);
            tte_write(option);

        }

        //se revisa si la hora actual coincide con la que se configuró en la alarma
        checkAlarm( (sec/600) % 6 , ((sec%3600)/60)%10, (sec/10)%6 , (sec%60)%10, &activeAlarm );

        oam_copy(oam_mem, buffer, 8 );
    }


    return 0;
}

