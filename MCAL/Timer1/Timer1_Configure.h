/*
 * Timer1_Configure.h
 *
 *  Created on: Oct 2, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_TIMER1_TIMER1_CONFIGURE_H_
#define MCAL_TIMER1_TIMER1_CONFIGURE_H_

/*****************************************************************************/
/*      					 OPTIONS FOR TIMER MODE:			             */
/* NORMAL - PHASE_CORRECT_8_BIT - PHASE_CORRECT_9_BIT - PHASE_CORRECT_10_BIT */
/* CTC_OCR1A - CTC_ICR1 - FAST_PWM_8_BIT - FAST_PWM_9_BIT - FAST_PWM_10_BIT  */
/* PHASE_AND_FREQUENCY_CORRECT_ICR1 - PHASE_AND_FREQUENCY_CORRECT_OCR1A      */
/* PHASE_CORRECT_ICR1 - PHASE_CORRECT_OCR1A - FAST_PWM_ICR1 - FAST_PWM_OCR1A */
/*																			 */
/* Note that modes ending with ICR1 means that the TOP value is determined	 */
/* by the ICR1 register, while those ending with OCR1A means that the TOP	 */
/* value is determined by the OCR1A register. Using OCR1A for setting TOP	 */
/* value prevents it from being used for generating a PWM output.  			 */
/*****************************************************************************/
#define MODE										NORMAL
/*****************************************************************************/


/*****************************************************************************/
/*  OPTIONS FOR OUTPUT COMPARE PIN (OC1A) BEHAVIOUR IN CASE OF NON-PWM MODE: */
/*       	DISCONNECT_OC1A - TOGGLE_OC1A - CLEAR_OC1A - SET_OC1A		     */
/*****************************************************************************/
#define OC1A_NON_PWM				  				TOGGLE_OC1A
/*****************************************************************************/


/*****************************************************************************/
/*  OPTIONS FOR OUTPUT COMPARE PIN (OC1B) BEHAVIOUR IN CASE OF NON-PWM MODE: */
/*       	DISCONNECT_OC1B - TOGGLE_OC1B - CLEAR_OC1B - SET_OC1B		     */
/*****************************************************************************/
#define OC1B_NON_PWM			  					TOGGLE_OC1B
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC1A) BEHAVIOUR IN CASE OF FAST PWM MODE: */
/* 			DISCONNECT_OC1A - NON_INVERTED_OC1A - INVERTED_OC1A	     	     */
/* TOGGLE_OC1A (FAST_PWM_OCR1A mode should be chosen. Otherwise, OC1A will	 */
/* be disconnected 															 */
/*****************************************************************************/
#define OC1A_FAST_PWM								NON_INVERTED_OC1A
/*****************************************************************************/


/*****************************************************************************/
/*  OPTIONS FOR OUTPUT COMPARE PIN (OC1B) BEHAVIOUR IN CASE OF NON-PWM MODE: */
/*       		  DISCONNECT_OC1B - NON_INVERTED_OC1B - INVERTED_OC1B  	 	 */
/*****************************************************************************/
#define OC1B_FAST_PWM			  					NON_INVERTED_OC1B
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC1A) BEHAVIOUR IN CASE OF PHASE CORRECT  */
/* 					   AND PHASE & FREQUENCY PWM MODES:  				     */
/* 				 DISCONNECT_OC1A - NON_INVERTED_OC1A - INVERTED_OC1A		 */
/* TOGGLE_OC1A (PHASE_AND_FREQUENCY_CORRECT_OCR1A or FAST_PWM_ICR1 mode		 */
/* should  be chosen. Otherwise, OC1A will be disconnected 					 */
/*****************************************************************************/
#define OC1A_PHASE									NON_INVERTED_OC1A
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC1B) BEHAVIOUR IN CASE OF PHASE CORRECT  */
/* 					   AND PHASE & FREQUENCY PWM MODES:  				     */
/* 			DISCONNECT_OC1B - NON_INVERTED_OC1B - INVERTED_OC1B    			 */
/*****************************************************************************/
#define OC1B_PHASE									NON_INVERTED_OC1B
/*****************************************************************************/


/*****************************************************************************/
/* 							OPTIONS FOR CLOCK SELECT	 					 */
/*        NO_CLOCK_SOURCE - NO_PRESCALER - PRESCALER_8 - PRESCALER_64	     */
/*	       PRESCALER_256 - PRESCALER_1024 - EXTERNAL_T0_FALLING_EDGE		 */
/* 							EXTERNAL_T0_RISING_EDGE 						 */
/*****************************************************************************/
#define CLOCK_SELECT								PRESCALER_8
/*****************************************************************************/


#endif /* MCAL_TIMER1_TIMER1_CONFIGURE_H_ */
