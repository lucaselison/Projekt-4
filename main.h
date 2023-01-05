#ifndef MAIN_H_
#define MAIN_H_

/* Klockfrekvens (behövs för fördröjningsrutiner): */
#define F_CPU 16000000UL /* 16 MHz. */

//Vilka biblotek som annvänds
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Definerar det som behövs
#define BUTTON1 PORTB5
#define TMP36 PORTC2

#define BUTTON1_IS_PRESSED (PINB & (1 << BUTTON1))

#define TIMER_INTERRUPT_MS 0.128 /* Tid mellan varje timergenererat avbrott. */

#define set(reg, bit) reg |= (1 << bit)
#define clr(reg, bit) reg &= ~(1 << bit)
#define read(reg, bit) (reg & (1 << bit))

extern volatile bool timer1_enable;

#endif /* MAIN_H_ */