

#include"system.h"
#include"DigitalOut.h"
#include"DigitalIn.h"

#define LED B0
#define BUTTON B1

void gpio_tests();

void gpio_poll_test();

void gpio_intr_test();

void Gpio_1_Callback();

void Gpio_Falling_Callback();