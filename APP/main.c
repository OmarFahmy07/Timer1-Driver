/*
 * main.c
 *
 *  Created on: Oct 3, 2020
 *      Author: Omar Fahmy
 */

/* HAL LAYER */
#include "../HAL/LCD/LCD_Interface.h"
/* MCAL LAYER */
#include "../MCAL/Timer1/Timer1_Interface.h"
#include "../MCAL/Timer0/Timer0_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/Global Interrupt/GI_Interface.h"

#include <util/delay.h>

#define TIMER1_PRESCALER	1024UL
#define FCLK				8000000UL

u8 trigger = TIMER1_RISING_EDGE;
u16 CountPeriod;
f32 Tperiod;
u16 CountOn;
f32 Ton;

void CEISR(void);

int main (void)
{
	LCD_U8Init();
	Timer0_U8Init();
	Timer1_U8Init();
	LCD_U8SendString("Ton: ");
	LCD_U8SetPosition(LCD_FIRST_ROW, LCD_TWELFTH_COLUMN);
	LCD_U8SendString("sec.");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("Ttot: ");
	LCD_U8SetPosition(LCD_FIRST_ROW, LCD_THIRTEENTH_COLUMN);
	LCD_U8SendString("sec.");
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT); //Event pin
	Timer0_U8SetDutyCycle(50);
	Timer1_U8Init();
	DIO_U8SetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT); //ICP1
	Timer1_U8CaptureEventEnableInterrupt();
	Timer1_U8CaptureEventSetCallBack(CEISR);
	Timer1_U8ICEdgeSelect(trigger);
	GI_U8Enable();
	Timer0_U8Start();
	Timer1_U8Start();

	while (1)
	{
		Ton = (f32)CountOn * TIMER1_PRESCALER / FCLK;
		Tperiod = (f32)CountPeriod * TIMER1_PRESCALER / FCLK;
		LCD_U8SetPosition(LCD_FIRST_ROW, LCD_SIXTH_COLUMN);
		LCD_U8SendNumber(Ton);
		LCD_U8SetPosition(LCD_SECOND_ROW, LCD_SEVENTH_COLUMN);
		LCD_U8SendNumber(Tperiod);
	}

	return 0;
}

void CEISR(void)
{
	if (TIMER1_RISING_EDGE == trigger)
	{
		Timer1_U8GetCapturedValue(&CountPeriod);
		Timer1_U8Preload(0);
		trigger = TIMER1_FALLING_EDGE;
		Timer1_U8ICEdgeSelect(trigger);
	}
	else if (TIMER1_FALLING_EDGE == trigger)
	{
		Timer1_U8GetCapturedValue(&CountOn);
		trigger = TIMER1_RISING_EDGE;
		Timer1_U8ICEdgeSelect(trigger);
	}
}
