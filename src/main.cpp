// this is only for the QtCreator to find the correct highlighting - this is already defined somewhere before
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ArduinoDrivers/arduinouno.hpp"

#include "ArduinoDrivers/shiftregister74hc595.hpp"
//#include "ArduinoDrivers/rslatchcd4043b.hpp"
//#include "ArduinoDrivers/parallelinshiftregister74hc165.hpp"

int main()
{
    typedef ArduinoUno arduinoUno;

    typedef ShiftRegister74HC595<8,
            arduinoUno::D2,
            arduinoUno::D5,
            arduinoUno::D4,
            arduinoUno::D3,
            arduinoUno::D6> shiftRegister;
    shiftRegister::initialize();
    shiftRegister::enableOutput();

    uint8_t data = 0xff;
    while (true)
    {
        shiftRegister::shiftInBits(&data);
        shiftRegister::showShiftRegister();
        _delay_ms(100);
        data--;
    }
}
