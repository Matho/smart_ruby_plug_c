/*****************************************************************************
* | File      	:   trst.h
* | Author      :   Waveshare team
* | Function    :   
* | Info        :
*
*----------------
* |	This version:   V1.0
* | Date        :   2019-07-03
* | Info        :   Basic version
*
******************************************************************************/

#ifndef _TRST_H_
#define _TRST_H_

void LCD_redraw(int screen_id, const char *message_line1, const char *message_line2, int waiting_for_key_press, int waiting_in_booting);
int KEY_listen(int ping_interval);


#endif