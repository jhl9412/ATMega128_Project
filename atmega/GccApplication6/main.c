#define F_CPU 14745600L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "lcd.h"
#include "servo.h"

extern int dis_r, dis_l, temp, humi;

void LCD_write_all(void);

int main(void)
{
	char msg[30]={0};
	
	sei();
	
	LCD_init();
	servo_init();
	uart_init();
	
	while (1)
	{
		memset(msg,'\0',30);
		get_msg(msg);
		LCD_write_all();
		servo();
	}
}
void LCD_write_all(void)
{
 	char temp1[8], temp2[8],temp3[8], temp4[8];

	if((dis_r>0&&dis_r<4000)&&dis_l>0&&dis_l<4000){
		if(dis_r>=1000)					sprintf(temp1, "R:%d",dis_r);
		else if(dis_r<1000&&dis_r>=100)	sprintf(temp1, "R: %d",dis_r);
		else if(dis_r>=10)				sprintf(temp1, "R:  %d",dis_r);
		else							sprintf(temp1, "R:   %d",dis_r);

		if(dis_l>=1000)					sprintf(temp2, "L:%d",dis_l);
		else if(dis_l<1000&&dis_l>=100) sprintf(temp2, "L: %d",dis_l );
		else if(dis_l>=10)				sprintf(temp2, "L:  %d",dis_l );
		else							sprintf(temp2, "L:   %d", dis_l );

		if(temp>=100)					sprintf(temp3, "T:%d",temp);
		else if(temp<100&&temp>=10)		sprintf(temp3, "T: %d",temp );
		
		if(humi>=100)					sprintf(temp4, "H:%d",humi);
		else if(humi<100&&humi>=10)		sprintf(temp4, "H: %d",humi );

		LCD_goto_XY(0,0);
		LCD_write_string(temp1);
		LCD_goto_XY(0,8);
		LCD_write_string(temp2);
		LCD_goto_XY(1,0);
		LCD_write_string(temp3);
		LCD_goto_XY(1,8);
		LCD_write_string(temp4);
	}
}