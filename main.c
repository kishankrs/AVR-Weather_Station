/*
 * DHT11.c
 *
 * Created: 27-11-2021 12.11.30 AM
 * Author : Gaurav
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "Lcd.h"
#include "DHT11.h"

uint8_t I_hum,D_hum,I_temp,D_temp,checksum;

int main(void)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	//char data[5];
	lcd_init(); //initialize lcd
	lcd_clear();
	lcd_gotoxy(1,1);
	lcd_Display_String("Humidity = ");
	lcd_gotoxy(1,2);
	lcd_Display_String("Temp = ");
	
    while (1) 
    {
		request();               //send start pulse
		response();              //receive confirmation
		I_hum = Receive_data();  //store 1st 1byte int data of humidity
		D_hum = Receive_data();  //store next 1byte decimal data of humidity
		I_temp= Receive_data();  //store next 1byte int data of temperature
		D_temp= Receive_data();  //store next 1byte decimal data of temperature
		checksum= Receive_data();//store next 1byte data in checksum for verification
		
		if ((I_hum + D_hum + I_temp + D_temp) != checksum)
		{
			lcd_gotoxy(1,1);
			lcd_Display_String("Error");
		}
		else
		{
			lcd_gotoxy(11,1);
			lcd_Display_Integer(I_hum);
			lcd_Display_String(".");
			lcd_Display_Integer(D_hum);
			lcd_Display_String("%");
			
			lcd_gotoxy(7,2);
			lcd_Display_Integer(I_temp);
			lcd_Display_String(".");
			lcd_Display_Integer(D_temp);
			lcd_Display_String("C");
			
			lcd_Display_String(" ");
			lcd_Display_Integer(checksum);
		}
		_delay_ms(10);
    }
}

