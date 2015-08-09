/**
 * File: startup.c
 * Description: Startup initialization code.
 * Author: Vijay Karthick Baskar.
 * License: Assume BSD type license and feel free to use this code.
 *			Sending me a thank you mail will do!
 */

/*
 *------------------------------------------------------------------------------
 * Include Files
 *------------------------------------------------------------------------------
 */

#include "startup.h"

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

int wdog_counter;

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
 * Public Function Definitions
 *------------------------------------------------------------------------------
 */

void disable_watchdog() {
	/* Disable the watchdog */
	WDTCTL = WDTPW | WDTHOLD;
}

void enable_watchdog() {
	/* Enable the watchdog */
	WDTCTL = WDTPW;
}

void clock_init() {
	/* Set the DCO frequency to 8 MHz */
	DCOCTL = DCO_8MHZ;

	/* Disable the external oscillator */
	BCSCTL1 = XT2OFF;

	/* Set the range select to produce 8 MHz frequency clock */
	BCSCTL1 |= RSEL_8MHZ;

	/* Select DCO as the clock source */
	BCSCTL2 &= ~(SELM1 | SELM0);

	/* Select the clock scaling factor as 1 */
	BCSCTL2 &= ~(DIVM1 | DIVM0);

	/* Set the sub module clock source as DCO */
	BCSCTL2 &= ~SELS;

	/* Set scaling factor for sub module clock as 8 to get 1 MHz frequency */
	BCSCTL2 |= (DIVS1 | DIVS0);

	/* Set the DCO resistor to be internal - internal resistor is not accurate */
	BCSCTL2 &= ~DCO_EXT_RESISTOR_ENABLE;
}

void init_wdog() {
	/**
	 * No changes required, as SMCLK is selected with scaler as 32768 = 32.768ms timeout by default
	 * i.e. 1/1MHz * 32768
	 */
}

void reset_wdog() {
	if (wdog_counter < MIN_REFRESH_VALUE) {
		wdog_counter++;
		return;
	}
	else {
		wdog_counter = 0;
		WDTCTL = WDTPW | WDTCNTCL;
	}
}

void gpio_init() {
	/* Settings for port 1 I/O */
	/* Pin 0 is SCK */
	PORT1_PRIMARY_FUNCTION(PORT1_PIN0_SPI);
	PORT1_DIR_OUTPUT(PORT1_PIN0_SPI);
	/* Pin 1 is MISO */
	PORT1_PRIMARY_FUNCTION(PORT1_PIN1_MISO);
	PORT1_DIR_INPUT(PORT1_PIN1_MISO);
	/* Pin 2 is MOSI */
	PORT1_PRIMARY_FUNCTION(PORT1_PIN0_SPI);
	PORT1_DIR_OUTPUT(PORT1_PIN0_SPI);
}

void delay_ms(int ms) {
	/* We compare with 30ms as the WDOG timeout value is 32.768ms */
	/* Number of cycles for 1 second delay = 8000000 cycles */
	/* Number of cycles for x ms delay = ((x * 8000000)/1000) cycles */
	/* Number of cycles for 10 ms delay = ((10 * 8000000)/1000) cycles = 80000 cycles */
	if (ms <= 10) {
		_delay_cycles(80000);
		reset_wdog();
	}
	else {
		int times = ms/10;
		int count;
		for (count=0; count<times; count++) {
			_delay_cycles(80000);
			reset_wdog();
			if (ms%10 > 5) {
				/* 10ms worth more clocks of delay to incorporate ms%30 remainder */
				_delay_cycles(80000);
				reset_wdog();
			}
		}
	}
}

void spi_init() {
	/* Configure the UCA0CTL0 register */
	UCA0CTL0 = SPI_MODE_ENABLE;
	UCA0CTL0 &= ~CLOCK_PHASE_CAPTURE_FIRST_EDGE;	//Data is changed on the first UCLK edge and captured on the following edge.
	UCA0CTL0 &= ~CLOCK_POLARITY_INACTIVE_ST_HIGH;	//The inactive state is low.
	UCA0CTL0 |= MSB_FIRST | DATA_7BIT | MASTER_MODE_ENABLE | SYNCH_MODE_ENABLE;

	/* Configure the UCA0CTL1 register */
	UCA0CTL1 = SPI_CLOCK_SRC_SMCLK | SOFTWARE_RESET_ENABLE;

	/* Configure the IE2 register */
	IE2 = TRANSMIT_INTERRUPT_ENABLE | RECEIVE_INTERRUPT_ENABLE;

	/* Configure the IFG2 register */
	IFG2 = TRANSMIT_INTERRUPT_PENDING | RECEIVE_INTERRUPT_PENDING;
}
