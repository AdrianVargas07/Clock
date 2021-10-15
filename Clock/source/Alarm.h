#ifndef ALARM
#define ALARM

#define TIME_OVERFLOW -1

int secondsUnitsAlarm = -1;
int secondsTensAlarm  = -1; 
int minutesUnitsAlarm = -1;
int minutesTensAlarm  = -1;

//metodo que permite configurar la alarma (solo configura minutos y segundos)
void alarm(OBJ_ATTR* buffer, int *activeAlarm){

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

    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));  

    char option[117] = {};
    snprintf(option, 117, "#{P:85,20} Alarm \t\t#{P:10,125} <- Back: Press A \t\t#{P:10,130} Set : B, Key Up, Key Left #{P:40,50}                  " );
    tte_write(option);

    int back = 0;

    //puntos de los segundos y los minutos
    tickSpriteAnimation(&spriteSecondsPoints,  10  );
    tickSpriteAnimation(&spriteMinutesPoints,  10  );
   
    while(!back){
        vid_vsync(); //sincronizar frames           
        
        key_poll();
        
        //para regresar al modo reloj
        if(key_hit(KEY_A)){
            char optionClock[107] = {};
            snprintf(optionClock, 107, "#{P:85,20} Clock        \t\t\t#{P:10,125} Alarm->Press A     \t\t#{P:10,130} Chronometer->Press B       " );
            tte_write(optionClock);
            back = 1;
        }

        //para configurar la alarma
        if(key_hit(KEY_B)){
            
             int option = 1;
             int frame = 0;

            //las siguientes lineas resetean los datos en caso de que se desee reconfigurar la alarma en la misma sesión
            char option2[32] = {};
            snprintf(option2, 32 , "#{P:50,90}                     " );
            tte_write(option2);
            tickSpriteAnimation(&spriteSecondsUnits,  0 );
            tickSpriteAnimation(&spriteSecondsTens,  0 );
            tickSpriteAnimation(&spriteMinutesUnits,  0 );
            tickSpriteAnimation(&spriteMinutesTens,  0 );
            oam_copy(oam_mem, buffer, 8 );

            //para configurar las unidades de los segundos
            while(option == 1){

                key_poll(); 

                //para marcar el digito seleccinado
                char select[15] = {};
                snprintf(select, 15, "#{P:168,90} ^" );
                tte_write(select);

                //incrementa el valor de las unidades de los segundos
                if( key_hit(KEY_UP) ){

                    frame++;
                    tickSpriteAnimation(&spriteSecondsUnits,  frame%10 );
                    oam_copy(oam_mem, buffer, 8 );

                    if (frame==10) {frame = 0;}

                }

                //guarda el valor escogido en las unidades de los segundos y pasa a configurar las decenas de los segundos
                if(key_hit(KEY_LEFT)){
                    secondsUnitsAlarm = frame;
                    option = 2; 
                }
                     
            }

            //para configurar las decenas de los segundos
            frame = 0;
            while(option == 2){

                key_poll(); 

                //para marcar el digito seleccinado
                char select[28] = {};
                snprintf(select, 28, "#{P:151,90} ^              " );
                tte_write(select);

                //incrementa el valor de las decenas de los segundos
                if( key_hit(KEY_UP) ){

                    frame++;
                    tickSpriteAnimation(&spriteSecondsTens,  frame%6 );
                    oam_copy(oam_mem, buffer, 8 );

                    if (frame==6) {frame = 0;}

                }

                //guarda el valor escogido en las unidades de los segundos y pasa a configurar las unidades de los minutos
                if(key_hit(KEY_LEFT)){
                    secondsTensAlarm = frame;
                    option = 3; 
                }
            }

            //para configurar las unidades de los minutos
            frame = 0;
            while(option == 3){

                 key_poll(); 

                //para marcar el digito seleccinado
                char select[40] = {};
                snprintf(select, 40, "#{P:120,90} ^                          " );
                tte_write(select);

                //incrementa el valor de las unidades de los minutos
                if( key_hit(KEY_UP) ){

                    frame++;
                    tickSpriteAnimation(&spriteMinutesUnits,  frame%10 );
                    oam_copy(oam_mem, buffer, 8 );

                    if (frame==10) {frame = 0;}

                }

                //guarda el valor escogido en las unidades de los segundos y pasa a las decenas de los minutos
                if(key_hit(KEY_LEFT)){
                    minutesUnitsAlarm = frame;
                    option = 4; 
                }
            }

            //para configurar las decenas de los minutos
            frame = 0;
            while(option == 4){

                 key_poll(); 
                
                //para marcar el digito seleccinado
                char select[55] = {};
                snprintf(select, 55, "#{P:100,90} ^                                         " );
                tte_write(select);

                //incrementa el valor de las decenas de los minutos
                if( key_hit(KEY_UP) ){

                    frame++;
                    tickSpriteAnimation(&spriteMinutesTens,  frame%6 );
                    oam_copy(oam_mem, buffer, 8 );

                    if (frame==6) {frame = 0;}

                }

                //guarda la hora configura por la alarma
                if(key_hit(KEY_B)){
                    minutesTensAlarm = frame;
                    *activeAlarm = 1;

                     option = 0; //sale de modo configuracion

                     char select[60] = {};
                     snprintf(select, 60, "#{P:50,90} Configured alarm!" );
                     tte_write(select);

                }
            }
            
        }

        oam_copy(oam_mem, buffer, 8 );    
   
    }

}

//metodo para revisar se la hora actual coincide con la que se configuró en la alarma
void checkAlarm(int minutesTens, int  minutesUnits, int secondsTens, int secondsUnits, int *activeAlarm){

    if(minutesTens == minutesTensAlarm && minutesUnits == minutesUnitsAlarm && secondsTens == secondsTensAlarm && secondsUnits == secondsUnitsAlarm){
        char alarm[31] = {}; 
        snprintf(alarm, 31, "#{P:50,50} Alarm ringing!    ");
        tte_write(alarm);

        *activeAlarm = 0;
    }
}

#endif