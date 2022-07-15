#include "DEV_Config.h"
#include "LCD_1in3.h"
#include "GUI_Paint.h"
#include "waveshare_header.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()


void LCD_redraw(int screen_id, const char *message_line1, const char *message_line2, int waiting_for_key_press, int waiting_in_booting)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);

    /* Module Init */
    if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }

    /* LCD Init */
    printf("Clibrary: starting display...\r\n");
    LCD_1in3_Init(HORIZONTAL);
    LCD_1in3_Clear(BLACK);

    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
//    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Clibrary: Failed to apply for black memory...\r\n");
        exit(0);
    }
    // printf("size = %d\r\n",sizeof(BlackImage) / sizeof(UWORD));
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, BLACK, 16);
    Paint_Clear(BLACK);

    // /* GUI */
    printf("Clibrary: drawing...\r\n");
//    // /*2.Drawing on the image*/

    printf("Clibrary: Passed scren_id is: %d\r\n",  screen_id );

    printf("Clibrary: Passed message_line1 is: %s\r\n",  message_line1);
    printf("Clibrary: Passed message_line2 is: %s\r\n",  message_line2);

    if (screen_id == 3 ){
        printf("Clibrary: Drawing BOOT screen \r\n");
        Paint_DrawRectangle(14, 14, 225, 225, ORANGE, DOT_PIXEL_13X13, DRAW_FILL_EMPTY);
        Paint_DrawString_EN(50, 80, "BOOT", &FontMenlo60, BLACK, ORANGE);

        int bootDelay = waiting_in_booting; // in seconds

        while(bootDelay > 0 ) {
            Paint_DrawRectangle(14, 14, 225, 225, ORANGE, DOT_PIXEL_13X13, DRAW_FILL_EMPTY);
            Paint_DrawString_EN(50, 80, "BOOT", &FontMenlo60, BLACK, ORANGE);

            Paint_DrawNum(40, 160, bootDelay, &FontMenlo40, ORANGE, IMAGE_BACKGROUND);
            DEV_Delay_ms(1);

            sleep(1);

            LCD_1in3_Display(BlackImage);
            Paint_Clear(BLACK);

            bootDelay--;
        }
    }


    if ( screen_id == 1) {
        printf("Clibrary: Drawing OK screen \r\n");
        Paint_DrawRectangle(14, 14, 225, 225, GREEN, DOT_PIXEL_13X13, DRAW_FILL_EMPTY);
        Paint_DrawString_EN(80, 80, "ON", &FontMenlo60, BLACK, GREEN);
    }
    else if (screen_id == 2) {
        printf("Clibrary: Drawing OFF screen \r\n");
        Paint_DrawRectangle(14, 14, 225, 225, BLUE, DOT_PIXEL_13X13, DRAW_FILL_EMPTY);
        Paint_DrawString_EN(60, 80, "OFF", &FontMenlo60, BLACK, BLUE);
    }
    else if (screen_id == 4) {
        printf("Clibrary: Drawing ERROR screen \r\n");
        Paint_DrawRectangle(14, 14, 225, 225, RED, DOT_PIXEL_13X13, DRAW_FILL_EMPTY);
        Paint_DrawString_EN(25, 25, "ERROR", &FontMenlo60, BLACK, RED);

        Paint_DrawString_EN(30, 90, message_line1, &FontMenlo40, BLACK, RED);
        Paint_DrawString_EN(30, 140, message_line2, &FontMenlo40, BLACK, RED);
    }

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1in3_Display(BlackImage);
    DEV_Delay_ms(1);

    printf("Clibrary: Going to exit ... \r\n");
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();
}




