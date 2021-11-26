#include <avr/io.h>
#include <util/delay.h>

#define DHT11_pin 6  //PD6

void request();
void response();
uint8_t Receive_data();