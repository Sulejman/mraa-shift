#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa.hpp"
#include "Shift.h"

Shift::Shift(int _SER_pin, int _RCLK_pin, int _SRCLK_pin, int _numberOfShifts) {
    
    SER_pin = new mraa::Gpio(_SER_pin);
    RCLK_pin = new mraa::Gpio(_RCLK_pin);
    SRCLK_pin = new mraa::Gpio(_SRCLK_pin);
    
    numberOfShifts = _numberOfShifts;
    numberOfPins = numberOfShifts * 8;
    registers = new bool[numberOfPins];

    clearRegisters();
}

Shift::~Shift() {
    delete[] registers;
    delete RCLK_pin;
    delete SRCLK_pin;
    delete SER_pin;
}

void Shift::clearRegisters() {
    setAll(1);
}

void Shift::writeRegisters() {
    int i;

    RCLK_pin->write(0);

    for (int i = numberOfPins - 1; i >= 0; i--) {
        SRCLK_pin->write(0);

        int val = registers[i];

        SER_pin->write(val);
        SRCLK_pin->write(1);
    }

    RCLK_pin->write(1);
}

void Shift::setRegister(int index, int value) {
    registers[index] = value;
    writeRegisters();
}

void Shift::setAll(int value) {
    for (int i = numberOfPins - 1; i >= 0; i--) {
        registers[i] = value;
    }

    writeRegisters();
}

void Shift::shiftOneByOne(int time, int position) {
    setAll(1);

    if (position == 1) {
        for (int i = 0; i <= numberOfPins; i++) {
            setRegister(i, 0);
            sleep(time);
            setRegister(i, 1);
        }
    }
    else if (position == 0) {
        for (int i = numberOfPins - 1; i >= 0; i--) {
            setRegister(i, 0);
            sleep(time);
            setRegister(i, 1);
        }
        setAll(1);
    }
    else {
        setAll(1);
    }
}
