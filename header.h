#ifndef HEADER_H_
#define HEADER_H_

#include "main.h"
#include "adc.h"
#include "timer.h"
#include "tmp36.h"
#include "Serial.h"

//Definerar namn till de olika structar och vad de har för uppgift
extern timer_t timer0, timer1;
extern tmp36_t temp1;

void setup(void);

#endif /* HEADER_H_ */