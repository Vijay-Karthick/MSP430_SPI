/**
 * File: startup.h
 * Description: Startup initialization code.
 * Author: Vijay Karthick Baskar.
 * License: Assume BSD type license and feel free to use this code.
 *			Sending me a thank you mail will do!
 */

#ifndef STARTUP_H_
#define STARTUP_H_

/*
 *------------------------------------------------------------------------------
 * Include Files
 *------------------------------------------------------------------------------
 */

#include <msp430g2553.h>

/*
 *------------------------------------------------------------------------------
 * Private Defines
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Private Macros
 *------------------------------------------------------------------------------
 */

/* Settings for various clock frequencies */
#define DCO_8MHZ				(DCO1|DCO0)
#define DCO_16MHZ				(DCO2|DCO1|DCO0)
#define RSEL_8MHZ				(RSEL3|RSEL2|RSEL0)
#define RSEL_16MHZ				(RSEL3|RSEL2|RSEL1|RSEL0)

/* Frequency of CPU is 8MHz */
#define F_CLOCK					(8000000)

/* Enable external resistor, as internal resistor is inaccurate */
#define DCO_EXT_RESISTOR_ENABLE	(0x01)

/*
 * Minimum refresh value of the counter used for WDOG:
 * value 2 indicates 20 ms; can't have value
 * 3 as overheads cross WDOG time of 32.768ms
 **/
#define MIN_REFRESH_VALUE		(2)

/* Defines for the GPIO */
#define PORT1_PIN0_LED1			(0b00000001)
#define PORT1_PIN1_MISO			(0b00000010)
#define PORT1_PIN2_MOSI			(0b00000100)
#define PORT1_PIN3_SWITCH2		(0b00001000)
#define PORT1_PIN4_GPIO			(0b00010000)
#define PORT1_PIN5_GPIO			(0b00100000)
#define PORT1_PIN6_LED2			(0b01000000)
#define PORT1_PIN7_GPIO			(0b10000000)
#define PORT2_PIN0_GPIO			(0b00000001)
#define PORT2_PIN1_GPIO			(0b00000010)
#define PORT2_PIN2_GPIO			(0b00000100)
#define PORT2_PIN3_GPIO			(0b00001000)
#define PORT2_PIN4_GPIO			(0b00010000)
#define PORT2_PIN5_GPIO			(0b00100000)
#define PORT2_PIN6_GPIO_XIN		(0b01000000)
#define PORT2_PIN7_GPIO_XOUT	(0b10000000)

/* Defines for MUX function for GPIO */
#define PORT1_GPIO_MODE(pinNumber)			{P1SEL &= ~pinNumber; P1SEL2 &= ~pinNumber;}
#define PORT1_PRIMARY_FUNCTION(pinNumber)	{P1SEL |= pinNumber; P1SEL2 &= ~pinNumber;}
#define PORT1_SECONDARY_FUNCTION(pinNumber)	{P1SEL |= pinNumber; P1SEL2 |= pinNumber;}
#define PORT2_GPIO_MODE(pinNumber)			{P2SEL &= ~pinNumber; P2SEL2 &= ~pinNumber;}
#define PORT2_PRIMARY_FUNCTION(pinNumber)	{P2SEL |= pinNumber; P2SEL2 &= ~pinNumber;}
#define PORT2_SECONDARY_FUNCTION(pinNumber)	{P2SEL |= pinNumber; P2SEL2 |= pinNumber;}

/* Defines for input */
#define PORT1_INPUT_LOW(pinNumber)			{P1IN &= ~pinNumber;}
#define PORT1_INPUT_HIGH(pinNumber)			{P1IN |= pinNumber;}
#define PORT2_INPUT_LOW(pinNumber)			{P2IN &= ~pinNumber;}
#define PORT2_INPUT_HIGH(pinNumber)			{P2IN |= pinNumber;}

/*Defines for output */
#define PORT1_OUTPUT_LOW(pinNumber)			{P1OUT &= ~pinNumber;}
#define PORT1_OUTPUT_HIGH(pinNumber)		{P1OUT |= pinNumber;}
#define PORT2_OUTPUT_LOW(pinNumber)			{P2OUT &= ~pinNumber;}
#define PORT2_OUTPUT_HIGH(pinNumber)		{P2OUT |= pinNumber;}

/* Defines for direction register - to set input or output */
#define PORT1_DIR_INPUT(pinNumber)			{P1DIR &= ~pinNumber;}
#define PORT1_DIR_OUTPUT(pinNumber)			{P1DIR |= pinNumber;}
#define PORT2_DIR_INPUT(pinNumber)			{P2DIR &= ~pinNumber;}
#define PORT2_DIR_OUTPUT(pinNumber)			{P2DIR |= pinNumber;}

/*Defines for push pull register enable */
#define PORT1_PULL_DOWN(pinNumber)			{P1REN &= ~pinNumber;}
#define PORT1_PULL_UP(pinNumber)			{P1REN |= pinNumber;}
#define PORT2_PULL_DOWN(pinNumber)			{P2REN &= ~pinNumber;}
#define PORT2_PULL_UP(pinNumber)			{P2REN |= pinNumber;}

/*
 *------------------------------------------------------------------------------
 * Private Data Types
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Public Variables
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Private Variables
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Public Constants
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Private Constants
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Private Function Prototypes
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * Public Function Prototypes
 *------------------------------------------------------------------------------
 */

void disable_watchdog();
void enable_watchdog();
void clock_init();
void init_wdog();
void reset_wdog();
void gpio_init();
void delay_ms(int ms);

#endif /* STARTUP_H_ */
