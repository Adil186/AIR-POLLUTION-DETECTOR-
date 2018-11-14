/*
 * mq15_sensor_.c
 *
 * Created: 02-06-2018 23:53:04
 *  Author: Kamran
 */ 



#include <avr/io.h>
# define F_CPU 8000000
# include <util/delay.h>
#include "lcd.h"
int main(void)
{  DDRC=0xFF;
	 int a;
	lcd_init();
	ADMUX=0x00;
	ADCSRA=0x86;
	lcd_comm(0x82);
	lcd_string("!Air Quality!");
	lcd_comm(0xC5);
	lcd_string("Detector");
	_delay_ms(5000);
	lcd_comm(0x01);
	while(1)
	{
		ADMUX=0x00;
		ADCSRA|=1<<ADSC;
		while((ADCSRA&(1<<ADIF))==0);
		ADCSRA|=1<<ADIF;
		lcd_comm(0x80);
		lcd_string("AQI =");
		lcd_comm(0x85);
		a=ADC;
		lcd_number(a);
		if(a>200)
		{
		lcd_comm(0xC2);
		lcd_string("Polluted!!");
		_delay_ms(500);
		lcd_comm(0x01);
		PORTC=0x01;
		}
		else
		{
			lcd_comm(0xC2);
			lcd_string("Not Polluted!!");
			_delay_ms(500);
			lcd_comm(0x01);
			PORTC=0x00;
		}
		
	}
}