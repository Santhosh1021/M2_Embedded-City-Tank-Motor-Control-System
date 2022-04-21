#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define LCD_Port PORTD      //Define LCD Port (PORTA, PORTB, PORTC, PORTD)
#define LCD_DPin  DDRD      //Define 4-Bit Pins (PD4-PD7 at PORT D)
#define RSPIN PD0     //RS Pin
#define ENPIN PD1       //E Pin
unsigned volatile FLAG=0;
      //Timer for LCD
void LCD_Init (void)
{
  LCD_DPin = 0xFF;    //Control LCD Pins (D4-D7)
  _delay_ms(15);    //Wait before LCD activation
  LCD_Action(0x02); //4-Bit Control
  LCD_Action(0x28);       //Control Matrix @ 4-Bit
  LCD_Action(0x0c);       //Disable Cursor
  LCD_Action(0x06);       //Move Cursor
  LCD_Action(0x01);       //Clean LCD
  _delay_ms(2);
}

void LCD_Action( unsigned char cmnd )
{
  LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
  LCD_Port &= ~ (1<<RSPIN);
  LCD_Port |= (1<<ENPIN);
  _delay_us(1);
  LCD_Port &= ~ (1<<ENPIN);
  _delay_us(200);
  LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
  LCD_Port |= (1<<ENPIN);
  _delay_us(1);
  LCD_Port &= ~ (1<<ENPIN);
  _delay_ms(2);
}

void LCD_Clear()
{
  LCD_Action (0x01);    //Clear LCD
  _delay_ms(2);     //Wait to clean LCD
  LCD_Action (0x80);    //Move to Position Line 1, Position 1
}


void LCD_Print (char *str)
{
  int i;
  for(i=0; str[i]!=0; i++)
  {
    LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0);
    LCD_Port |= (1<<RSPIN);
    LCD_Port|= (1<<ENPIN);
    _delay_us(1);
    LCD_Port &= ~ (1<<ENPIN);
    _delay_us(200);
    LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4);
    LCD_Port |= (1<<ENPIN);
    _delay_us(1);
    LCD_Port &= ~ (1<<ENPIN);
    _delay_ms(2);
  }
}
//Write on a specific location
void LCD_Printpos (char row, char pos, char *str)
{
  if (row == 0 && pos<16)
  LCD_Action((pos & 0x0F)|0x80);
  else if (row == 1 && pos<16)
  LCD_Action((pos & 0x0F)|0xC0);
  LCD_Print(str);
}

int main()
{
  DDRC |=(1<<0);
  DDRC |=(1<<1);
  DDRB &= ~(1<<0);
  DDRB &= ~(1<<1);
  DDRB &= ~(1<<2);
  EICRA|=(1<<ISC00);
  EIMSK|=(1<<INT0);
  sei();
  LCD_Init(); //Activate LCD
  LCD_Print("City tank tatus"); //Begin writing at Line 1, Position 1

  while(1) {
   LCD_Action(0xC0);   //Go to Line 2, Position 1
    //Initialize the components


       if (!(PINB & (1<<0))==0)
    {
      PORTC |= (1<<PORTC0);
      PORTC |= (1<<PORTC1);
       LCD_Print("2 Motor on ");
    }
    else if(!(PINB & (1<<1))==0)
    {
      PORTC |= (1<<PORTC0);
      PORTC &= ~(1<<PORTC1);
       LCD_Print("1 Motor on ");
    }
   else if(!(PINB & (1<<2))==0)
    {
      PORTC &= ~(1<<PORTC0);
      PORTC &= ~(1<<PORTC1);
       LCD_Print("2 Motor off ");
   }
   else if(FLAG==1)
   {
      // PORTC &= ~(1<<PORTC0);
      //PORTC &= ~(1<<PORTC1);
      LCD_Clear();
     // _delay_us(200);
        _delay_ms(2000);
       LCD_Print("2 Motor oOO ");
       FLAG=0;
   }
  }
  return 0;
}
ISR(INT0_vect)
{
PORTB^=(1<<PORTB0);
    FLAG=1;
}
