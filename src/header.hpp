#ifndef HEADER_HPP
#define HEADER_HPP
#include "mbed.h"

extern PwmOut lights[];
extern InterruptIn button;
enum position{blue, orange};
int position = blue;

void start_timer();
void transition();
void intesity();
void blink_blue();
void blink_orange();
void rising();
void falling();
void blink_off();

#endif