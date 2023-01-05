#include "Header.h"

//Alla interrupts som beh�vs f�r att kunna temp sensorn och knappen som har ett studs skydd.
ISR(PCINT0_vect)
{
	PCICR &= ~(1 << PCIE0);//�veriga bitars bibeh�ller
	TIMSK0 = (1 << TOIE0);//S�tter timer 0 till 300 ms
	
	
	if(BUTTON1_IS_PRESSED)
	{
		tmp36_temp_print(&temp1);// M�t temp.
		timer_reset_counter(&timer1);// Nollst�ll timer1.
	}
	return;
}

ISR (TIMER0_OVF_vect)
{
	timer_count(&timer0);
	
	if (timer_elapsed(&timer0))
	{
		PCICR |= (1 << PCIE0);
		timer_disable_interrupt(&timer0);
	}
}

ISR (TIMER1_COMPA_vect)
{
	timer_count(&timer1);

	if (timer_elapsed(&timer1))
	{
		tmp36_temp_print(&temp1);
	}

	return;
}