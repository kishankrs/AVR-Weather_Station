//**********************************************************
//                    DHT11 Library
//            Temperature and Humidity Sensor
//**********************************************************
#include <avr/io.h>
#include <util/delay.h>

#define DHT11_pin 2  //PD2

void request();
void response();
uint8_t Receive_data();