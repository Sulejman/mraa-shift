#ifndef SHIFT_H
#define SHIFT_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa.hpp"

class Shift {

public:
    Shift(int _SER_pin, int _RCLK_pin, int _SRCLK_pin, int _numberOfShifts);
    ~Shift();

    void clearRegisters();
    void writeRegisters();


    void setRegister(int index, int value); 	// setting register,index(number of register) , 
    						// and value (LOW or HIGH)
    void setAll(int value); 			// set all registers to value(HIGH or LOW)
    void shiftOneByOne(int delay, int position);	// shifting outputs , time(delay) 
    							// and poz (1= from first to last , 
							// 0= from last to first)
private:
    mraa::Gpio* SER_pin;
    mraa::Gpio* RCLK_pin;
    mraa::Gpio* SRCLK_pin;
    int numberOfShifts;
    int numberOfPins;
    bool *registers; // Since we don't know array size in header, we define it as a pointer
};

#endif //SHIFT_H
