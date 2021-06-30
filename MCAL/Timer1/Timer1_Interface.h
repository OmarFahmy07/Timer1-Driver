/*
 * Timer1_Interface.h
 *
 *  Created on: Oct 2, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_TIMER1_TIMER1_INTERFACE_H_
#define MCAL_TIMER1_TIMER1_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/***********************************************************************************/
/* 						USEFUL MACROS AS FUNCTIONS' ARGUMENTS   				   */
/***********************************************************************************/

/***********************************************************************************/
/*         					INPUT CAPTURE EDGE SELECT      						   */
/***********************************************************************************/
#define TIMER1_FALLING_EDGE								0
#define TIMER1_RISING_EDGE								1
/***********************************************************************************/


/************************************************************************************/
/*							 FUNCTIONS PROTOTYPES								    */
/************************************************************************************/

/************************************************************************************/
/* Description: initializes timer1's peripheral	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: sets a value to start counting from								    */
/* Inputs: value to count from													 	*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8Preload(const u16 LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: sets a value to overflow at in non-normal modes. The minimum value	*/
/* allowed is 0x0003. 					    										*/
/* Inputs: TOP value												 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8SetCounterTOP(const u16 LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: sets the value to be compared with for Output Compare unit A 		*/
/* Inputs: value to compare with									 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8SetOCACompareValue(const u16 LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: sets the value to be compared with for Output Compare unit B 		*/
/* Inputs: value to compare with									 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8SetOCBCompareValue(const u16 LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a PWM signal with the received duty cycle (0% - 100%) on		*/
/* OC1A pin.																		*/
/* Inputs: Duty cycle - Counter top value (minimum 0x0003)			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OC1ASetDutyCycle(const f32 LOC_F32DutyCycle, const u16 LOC_U16Top);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a PWM signal with the received duty cycle (0% - 100%) on		*/
/* OC1B pin.																		*/
/* Inputs: Duty cycle - Counter top value (minimum 0x0003)			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OC1BSetDutyCycle(const f32 LOC_F32DutyCycle, const u16 LOC_U16Top);
/************************************************************************************/

/************************************************************************************/
/* Description: returns the value in timer1's counter. Counts are in the range of   */
/* 0 - 65535.					    													*/
/* Inputs: pointer to a variable to receive the value in			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8GetCounterValue(u16* const LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: activates the Input Capture Noise Canceler. When the Noise			*/
/* Canceler is activated, the input from the Input Capture Pin (ICP1) is filtered.	*/
/* Notice that The input capture is delayed by four Oscillator cycles when the 		*/
/* Noise Canceler is enabled														*/
/* Inputs: nothing			 	 		    										*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8EnableNoiseCanceler(void);
/************************************************************************************/

/************************************************************************************/
/* Description: deactivates the Input Capture Noise Canceler. 						*/
/* Inputs: nothing			 	 		    										*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8DisableNoiseCanceler(void);
/************************************************************************************/

/************************************************************************************/
/* Description: selects which edge on the Input Capture Pin (ICP1) that is used to	*/
/* trigger a capture event. 														*/
/* Inputs: nothing			 	 		    										*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8ICEdgeSelect(const u8 LOC_U8Edge);
/************************************************************************************/

/************************************************************************************/
/* Description: gets the value captured on the Input Capture Pin (ICP1). ICR1		*/
/* should not be used for defining TOP in this case in order to function correctly.	*/
/* Inputs: pointer to a variable to receive the value in							*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8GetCapturedValue(u16* const LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: enables overflow interrupt										    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8EnableOVFInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables overflow interrupt										    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8DisableOVFInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Output Compare A Match interrupt enable							    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OCAEnableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Output Compare A Match interrupt disable						    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OCADisableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Output Compare B Match interrupt enable							    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OCBEnableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Output Compare B Match interrupt disable						    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8OCBDisableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Capture Event interrupt enable									    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8CaptureEventEnableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: Capture Event interrupt disable									    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer1_U8CaptureEventDisableInterrupt(void);
/************************************************************************************/

/***********************************************************************************/
/* Description: polls on timer1 overflow's flag						 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OVFPollingOnFlag(void);
/***********************************************************************************/

/***********************************************************************************/
/* Description: polls on timer1 Output Compare A Match flag			 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OCAPollingOnFlag(void);
/***********************************************************************************/

/***********************************************************************************/
/* Description: polls on timer1 Output Compare B Match flag			 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OCBPollingOnFlag(void);
/***********************************************************************************/

/***********************************************************************************/
/* Description: polls on timer1 Capture Event flag					 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8CaptureEventPollingOnFlag(void);
/***********************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the overflow interrupt.  								 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OVFSetCallBack( void (*ptrToFun)(void) );
/***********************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the Output Compare A Match flag						 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OCASetCallBack( void (*ptrToFun)(void) );
/***********************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the Output Compare B Match flag						 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8OCBSetCallBack( void (*ptrToFun)(void) );
/***********************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the Capture Event flag								 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8CaptureEventSetCallBack( void (*ptrToFun)(void) );
/***********************************************************************************/

/***********************************************************************************/
/* Description: restarts timer1's prescaler. Note that this	affects both timer0	   */
/* and timer1						 			   			   					   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer1_U8ResetPrescaler(void);
/***********************************************************************************/


#endif /* MCAL_TIMER1_TIMER1_INTERFACE_H_ */
