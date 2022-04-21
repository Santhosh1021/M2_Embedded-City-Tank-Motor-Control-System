/**
 * @file /**
 * @file /**
 * @file motor_control.h
 * @author santhosh A
 * @brief Header file for motor control with functions
 *
 */

#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__


#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
/**
* @brief lcd initialization
* @return 
*/
void LCD_Init (void)

/**
* @brief lcd action
* @param[in] cmd
* @return 
*/
void LCD_Action( unsigned char cmnd )

/**
* @brief clears character.
* @return 
*/
void LCD_Clear()
/**
* @brief lcd print
* @param[in] str
* @return displays in lcd
void LCD_Print (char *str)

/**
* @brief lcd print
* @param[in1] row
* @param[in2] pos
* @param[in3] str
* @return print in lcd
*/
void LCD_Printpos (char row, char pos, char *str)

#endif  /* #define MOTOR_CONTROL_H */
