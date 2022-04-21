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
  LCD_Print("City tank Status"); //Begin writing at Line 1, Position 1

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
