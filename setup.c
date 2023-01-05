#include "Header.h"

timer_t timer0, timer1;
tmp36_t temp1;

static inline void init_ports(void)
{
	PORTB = (1 << BUTTON1);
	return;
}

static inline void init_interrupts(void)
{
	PCICR = (1 << PCINT0); // Aktiverar avbrott PCINT0_vect
	PCMSK0 = (1 << BUTTON1); //Aktiver avbrott på knapparna
	return;
}

void setup(void)
{
	tmp36_init(&temp1,PORTC2);
	
	init_ports();
	init_interrupts();
	
	timer_init(&timer0, TIMER_SEL_0, 300);
	
	timer_init(&timer1, TIMER_SEL_1, 60000);
	timer_enable_interrupt(&timer1);
	
	tmp36_temp_print(&temp1);
}