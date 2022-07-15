#include "DEV_Config.h"
#include "LCD_1in3.h"
#include "waveshare_header.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

/************************************
When using the button
Please execute
    sudo nano /boot/config.txt
Add at the end
    gpio=6,19,5,26,13,21,20,16=pu
*************************************/
int KEY_listen(int waiting_for_key_press)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);

    /* Module Init */
    if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
//    printf("Use this routine to add gpio=6,19,5,26,13,21,20,16=pu at the end of /boot/config.txt\r\n");

    /* Monitor button */
    printf("Clibrary: Listening on KEY\r\n");
    int key_pressed = 0;
    int i = 0;

    while(i <= waiting_for_key_press){
        if ((GET_KEY_UP == 0) || (GET_KEY_DOWN == 0) || (GET_KEY_LEFT == 0) || (GET_KEY_RIGHT == 0) || (GET_KEY_PRESS == 0) || (GET_KEY1 == 0) || (GET_KEY2 == 0) || (GET_KEY3 == 0) ) {
            printf("Clibrary: Key was pressed, exiting \r\n");
            key_pressed = 1;

            break;
        }

        sleep(1);
        i++;
    }

    DEV_ModuleExit();
    return key_pressed;
}

