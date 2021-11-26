#include "DHT11.h"

void request()   //send start pulse to dht
{
	DDRD |= (1<<DHT11_pin);    //set pin to output mode
	PORTD &= ~(1<<DHT11_pin);  //send low pulse
	_delay_ms(20);             //for 20ms
	PORTD |= (1<<DHT11_pin);   //set high
}

void response()   //get response/confirmation from DHT11
{
	DDRD &= ~(1<<DHT11_pin);            //set pin to input mode
	while(PIND & (1<<DHT11_pin));       //wait for low pulse   00000110 & 01000000 =00000000
	while((PIND & (1<<DHT11_pin)) ==0); //wait for high pulse
	while(PIND & (1<<DHT11_pin));       //wait for low pulse
}

uint8_t Receive_data()  //receive data from dht11
{
	uint8_t q,c;
	for ( q=0; q<8; q++)
	{
		while ((PIND & (1<<DHT11_pin)) == 0); //check for 0 bit and wait till high
		_delay_us(30);                        //wait for 30us
		if (PIND & (1<<DHT11_pin))            //if high >30us
			c = (c<<1)|(0x01);                //it is logic HIGH
		else
			c= (c<<1);                        //else it is logic LOW
		while(PIND & (1<<DHT11_pin));         //wait for 1 bit data pulse to finish(get low)
	}
	return c;
}