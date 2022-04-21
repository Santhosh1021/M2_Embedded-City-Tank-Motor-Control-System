#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define LCD_Port PORTD      //Define LCD Port (PORTA, PORTB, PORTC, PORTD)
#define LCD_DPin  DDRD      //Define 4-Bit Pins (PD4-PD7 at PORT D)
#define RSPIN PD0     //RS Pin
#define ENPIN PD1       
