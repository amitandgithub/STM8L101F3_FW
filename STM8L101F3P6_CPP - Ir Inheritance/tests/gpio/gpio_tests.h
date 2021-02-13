

#include"system.h"
#include"DigitalOut.h"
#include"DigitalIn.h"

#define LED B1
#define BUTTON C4

void gpio_tests();

void gpio_poll_test();

void gpio_intr_test();

void Gpio_1_Callback();

void Gpio_Callback();


extern DigitalIn<BUTTON,INPUT_FLOATING_INTERRUPT,INTERRUPT_ON_RISING,Gpio_Callback> Button;