/*
 * Timer1_Program.c
 *
 *  Created on: Oct 2, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* MCAL LAYER */
#include "Timer1_Configure.h"
#include "Timer1_Private.h"

/* Global Pointers to Functions for Calling Back */
void (*GLOB_VidTimer1OVFPtrCallBack)(void) = NULL;
void (*GLOB_VidTimer1OCAPtrCallBack)(void) = NULL;
void (*GLOB_VidTimer1OCBPtrCallBack)(void) = NULL;
void (*GLOB_VidTimer1CaptureEventPtrCallBack)(void) = NULL;

/************************************************************************************/
/*						PUBLIC FUNCTIONS IMPLEMENTATION								*/
/************************************************************************************/

u8 Timer1_U8Init(void)
{
	/* Mode of Operation Configuration */
#if MODE == NORMAL
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_CORRECT_8_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_CORRECT_9_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_CORRECT_10_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == CTC_OCR1A
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == FAST_PWM_8_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == FAST_PWM_9_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == FAST_PWM_10_BIT
	CLR_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_AND_FREQUENCY_CORRECT_ICR1
	SET_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_AND_FREQUENCY_CORRECT_OCR1A
	SET_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_CORRECT_ICR1
	SET_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == PHASE_CORRECT_OCR1A
	SET_BIT(TCCR1B_REGISTER, WGM13);
	CLR_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == CTC_ICR1
	SET_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	CLR_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == FAST_PWM_ICR1
	SET_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	CLR_BIT(TCCR1A_REGISTER, WGM10);

#elif MODE == FAST_PWM_OCR1A
	SET_BIT(TCCR1B_REGISTER, WGM13);
	SET_BIT(TCCR1B_REGISTER, WGM12);
	SET_BIT(TCCR1A_REGISTER, WGM11);
	SET_BIT(TCCR1A_REGISTER, WGM10);

#else
#error "Invalid mode of operation for timer1"
#endif

	/* Output Compare Pins Behavior */
#if MODE == CTC_ICR1 || MODE == CTC_OCR1A || MODE == NORMAL
#if OC1A_NON_PWM == DISCONNECT_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_NON_PWM == TOGGLE_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_NON_PWM == CLEAR_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_NON_PWM == SET_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#else
#error "Incorrect output compare pin (OC1A) behavior in case of non-PWM mode"
#endif
#if OC1B_NON_PWM == DISCONNECT_OC1B
	CLR_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_NON_PWM == TOGGLE_OC1B
	CLR_BIT(TCCR1A_REGISTER, COM1B1);
	SET_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_NON_PWM == CLEAR_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_NON_PWM == SET_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	SET_BIT(TCCR1A_REGISTER, COM1B0);
#else
#error "Incorrect output compare pin (OC1B) behavior in case of non-PWM mode"
#endif
#elif MODE == FAST_PWM_10_BIT || MODE == FAST_PWM_9_BIT || MODE == FAST_PWM_8_BIT \
   || MODE == FAST_PWM_ICR1 || MODE == FAST_PWM_OCR1A
#if OC1A_FAST_PWM == DISCONNECT_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_FAST_PWM == TOGGLE_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_FAST_PWM == NON_INVERTED_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_FAST_PWM == INVERTED_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#else
#error "Incorrect output compare pin (OC1A) behavior in case of fast PWM mode"
#endif
#if OC1B_FAST_PWM == DISCONNECT_OC1B
	CLR_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_FAST_PWM == NON_INVERTED_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_FAST_PWM == INVERTED_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	SET_BIT(TCCR1A_REGISTER, COM1B0);
#else
#error "Incorrect output compare pin (OC1B) behavior in case of fast PWM mode"
#endif
#elif MODE == PHASE_AND_FREQUENCY_CORRECT_ICR1 || MODE == PHASE_CORRECT_10_BIT  || \
	  MODE == PHASE_AND_FREQUENCY_CORRECT_OCR1A || MODE == PHASE_CORRECT_9_BIT || \
	  MODE == PHASE_CORRECT_8_BIT || MODE == PHASE_CORRECT_ICR1 || MODE == \
	  PHASE_CORRECT_OCR1A
#if OC1A_PHASE == DISCONNECT_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_PHASE == TOGGLE_OC1A
	CLR_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_PHASE == NON_INVERTED_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	CLR_BIT(TCCR1A_REGISTER, COM1A0);
#elif OC1A_PHASE == INVERTED_OC1A
	SET_BIT(TCCR1A_REGISTER, COM1A1);
	SET_BIT(TCCR1A_REGISTER, COM1A0);
#else
#error "Incorrect output compare pin (OC1A) behavior in case of phase correct or phase and frequency correct PWM modes"
#endif
#if OC1B_PHASE == DISCONNECT_OC1B
	CLR_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_PHASE == NON_INVERTED_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	CLR_BIT(TCCR1A_REGISTER, COM1B0);
#elif OC1B_PHASE == INVERTED_OC1B
	SET_BIT(TCCR1A_REGISTER, COM1B1);
	SET_BIT(TCCR1A_REGISTER, COM1B0);
#else
#error "Incorrect output compare pin (OC1B) behavior in case of phase correct or phase and frequency correct PWM modes"
#endif
#endif
	/* To ensure compatibility with future devices */
	CLR_BIT(TCCR1A_REGISTER, FOC1A);
	CLR_BIT(TCCR1A_REGISTER, FOC1B);
	CLR_BIT(TCCR1B_REGISTER, BIT5);
#if CLOCK_SELECT == NO_CLOCK_SOURCE
	CLR_BIT(TCCR1B_REGISTER, CS12);
	CLR_BIT(TCCR1B_REGISTER, CS11);
	CLR_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == NO_PRESCALER
	CLR_BIT(TCCR1B_REGISTER, CS12);
	CLR_BIT(TCCR1B_REGISTER, CS11);
	SET_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == PRESCALER_8
	CLR_BIT(TCCR1B_REGISTER, CS12);
	SET_BIT(TCCR1B_REGISTER, CS11);
	CLR_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == PRESCALER_64
	CLR_BIT(TCCR1B_REGISTER, CS12);
	SET_BIT(TCCR1B_REGISTER, CS11);
	SET_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == PRESCALER_256
	SET_BIT(TCCR1B_REGISTER, CS12);
	CLR_BIT(TCCR1B_REGISTER, CS11);
	CLR_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == PRESCALER_1024
	SET_BIT(TCCR1B_REGISTER, CS12);
	CLR_BIT(TCCR1B_REGISTER, CS11);
	SET_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == EXTERNAL_T0_FALLING_EDGE
	SET_BIT(TCCR1B_REGISTER, CS12);
	SET_BIT(TCCR1B_REGISTER, CS11);
	CLR_BIT(TCCR1B_REGISTER, CS10);
#elif CLOCK_SELECT == EXTERNAL_T0_RISING_EDGE
	SET_BIT(TCCR1B_REGISTER, CS12);
	SET_BIT(TCCR1B_REGISTER, CS11);
	SET_BIT(TCCR1B_REGISTER, CS10);
#else
#error "Incorrect clock selection"
#endif
	return NO_ERROR;
}

u8 Timer1_U8Preload(const u16 LOC_U16Value)
{
	TCNT1_REGISTER = LOC_U16Value;
	return NO_ERROR;
}

u8 Timer1_U8SetCounterTOP(const u16 LOC_U16Value)
{
	if (LOC_U16Value >= MINIMUM_RESOLUTION)
	{
#if MODE == CTC_OCR1A || MODE == FAST_PWM_OCR1A || MODE == PHASE_CORRECT_OCR1A \
		|| MODE == PHASE_AND_FREQUENCY_CORRECT_OCR1A
		OCR1A_REGISTER = LOC_U16Value;
#elif MODE == CTC_ICR1 || MODE == FAST_PWM_ICR1 || MODE == PHASE_CORRECT_ICR1 \
		|| MODE == PHASE_AND_FREQUENCY_CORRECT_ICR1
		ICR1_REGISTER = LOC_U16Value;
#elif MODE == NORMAL || MODE == PHASE_CORRECT_10_BIT || MODE == PHASE_CORRECT_8_BIT    \
		|| MODE == PHASE_CORRECT_9_BIT || MODE == FAST_PWM_10_BIT || MODE == FAST_PWM_9_BIT \
		|| MODE == FAST_PWM_8_BIT
		/* Trying to set TOP value while using a fixed-TOP mode. */
		return ERROR;
#else
#error "Invalid mode of operation for timer1"
#endif
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8SetOCACompareValue(const u16 LOC_U16Value)
{
#if MODE == CTC_OCR1A || MODE == PHASE_AND_FREQUENCY_CORRECT_OCR1A || MODE == \
		PHASE_CORRECT_OCR1A
	/* Trying to set the OCR1A value as a compare value while using OCR1A as a TOP */
	return ERROR;
#else
	OCR1A_REGISTER = LOC_U16Value;
	return NO_ERROR;
#endif
}

u8 Timer1_U8SetOCBCompareValue(const u16 LOC_U16Value)
{
	OCR1B_REGISTER = LOC_U16Value;
	return NO_ERROR;
}

u8 Timer1_U8OC1ASetDutyCycle(const f32 LOC_F32DutyCycle, const u16 LOC_U16Top)
{
	if (LOC_F32DutyCycle >= MINIMUM_DUTYCYCLE && LOC_F32DutyCycle <= MAXIMUM_DUTYCYCLE && LOC_U16Top >= MINIMUM_RESOLUTION)
	{
		Timer1_U8SetCounterTOP(LOC_U16Top);
		Timer1_U8SetOCACompareValue( ( LOC_F32DutyCycle / 100 ) * ( LOC_U16Top ) );
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8OC1BSetDutyCycle(const f32 LOC_F32DutyCycle, const u16 LOC_U16Top)
{
	if (LOC_F32DutyCycle <= MAXIMUM_DUTYCYCLE && LOC_U16Top >= MINIMUM_RESOLUTION)
	{
		Timer1_U8SetCounterTOP(LOC_U16Top);
		Timer1_U8SetOCBCompareValue( ( LOC_F32DutyCycle / 100 ) * ( LOC_U16Top ) );
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8GetCounterValue(u16* const LOC_U16Value)
{
	if (LOC_U16Value != NULL)
	{
		*LOC_U16Value = TCNT1_REGISTER;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8EnableNoiseCanceler(void)
{
	SET_BIT(TCCR1B_REGISTER, ICNC1);
	return NO_ERROR;
}

u8 Timer1_U8DisableNoiseCanceler(void)
{
	CLR_BIT(TCCR1B_REGISTER, ICNC1);
	return NO_ERROR;
}

u8 Timer1_U8ICEdgeSelect(const u8 LOC_U8Edge)
{
	switch (LOC_U8Edge)
	{
		case FALLING_EDGE:
		CLR_BIT(TCCR1B_REGISTER, ICES1);
		return NO_ERROR;

		case RISING_EDGE:
		SET_BIT(TCCR1B_REGISTER, ICES1);
		return NO_ERROR;

		default:
		return ERROR;
	}
}

u8 Timer1_U8GetCapturedValue(u16* const LOC_U16Value)
{
	if (LOC_U16Value != NULL)
	{

		*LOC_U16Value = ICR1_REGISTER;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8EnableOVFInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, TOIE1);
	return NO_ERROR;
}

u8 Timer1_U8DisableOVFInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, TOIE1);
	return NO_ERROR;
}

u8 Timer1_U8OCAEnableInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, OCIE1A);
	return NO_ERROR;
}

u8 Timer1_U8OCADisableInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, OCIE1A);
	return NO_ERROR;
}

u8 Timer1_U8OCBEnableInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, OCIE1B);
	return NO_ERROR;
}

u8 Timer1_U8OCBDisableInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, OCIE1B);
	return NO_ERROR;
}

u8 Timer1_U8CaptureEventEnableInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, TICIE1);
	return NO_ERROR;
}

u8 Timer1_U8CaptureEventDisableInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, TICIE1);
	return NO_ERROR;
}

u8 Timer1_U8OVFPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, TOV1) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, TOV1);
	return NO_ERROR;
}

u8 Timer1_U8OCAPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, OCF1A) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, OCF1A);
	return NO_ERROR;
}

u8 Timer1_U8OCBPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, OCF1B) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, OCF1B);
	return NO_ERROR;
}

u8 Timer1_U8CaptureEventPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, ICF1) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, ICF1);
	return NO_ERROR;
}

u8 Timer1_U8OVFSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer1OVFPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8OCASetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer1OCAPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8OCBSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer1OCBPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8CaptureEventSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer1CaptureEventPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer1_U8ResetPrescaler(void)
{
	SET_BIT(SFIOR_REGISTER, PSR10);
	return NO_ERROR;
}

/************************************************************************************/
/*						PRIVATE FUNCTIONS IMPLEMENTATION							*/
/************************************************************************************/

void __vector_9(void)
{
	if (GLOB_VidTimer1OVFPtrCallBack != NULL)
	{
		(*GLOB_VidTimer1OVFPtrCallBack)();
	}
}

void __vector_8(void)
{
	if (GLOB_VidTimer1OCBPtrCallBack != NULL)
	{
		(*GLOB_VidTimer1OCBPtrCallBack)();
	}
}

void __vector_7(void)
{
	if (GLOB_VidTimer1OCAPtrCallBack != NULL)
	{
		(*GLOB_VidTimer1OCAPtrCallBack)();
	}
}

void __vector_6(void)
{
	if (GLOB_VidTimer1CaptureEventPtrCallBack != NULL)
	{
		(*GLOB_VidTimer1CaptureEventPtrCallBack)();
	}
}
