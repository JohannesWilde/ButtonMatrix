// this is only for the QtCreator to find the correct highlighting - this is already defined somewhere before
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ArduinoDrivers/arduinouno.hpp"
#include "ArduinoDrivers/dummytypes.hpp"

#include "ArduinoDrivers/rslatch.hpp"
#include "ArduinoDrivers/parallelinshiftregister74hc165.hpp"
#include "ArduinoDrivers/shiftregister74hc595.hpp"

int main()
{
    typedef ArduinoUno arduinoUno;

    typedef arduinoUno::pinC5 VccPeriphery;
    VccPeriphery::setType(AvrInputOutput::OutputHigh);

    typedef RsLatch<DummyAvrPin1, arduinoUno::pinC1, DummyAvrPin1> rsLatch;
    rsLatch::initialize();

    typedef ParallelInShiftRegister74HC165<8,
            arduinoUno::pinC3,
            arduinoUno::pinC2,
            DummyAvrPin1,
            arduinoUno::pinC4,
            DummyAvrPin1,
            DummyAvrPin1> parallelInShiftRegister;
    parallelInShiftRegister::initialize();

    typedef ShiftRegister74HC595<8,
            arduinoUno::pinD2,
            arduinoUno::pinD5,
            arduinoUno::pinD4,
            arduinoUno::pinD3,
            arduinoUno::pinD6> shiftRegister;
    shiftRegister::initialize();


    parallelInShiftRegister::enableClock();
    shiftRegister::enableOutput();
    rsLatch::reset();



    uint8_t data = 0xff;
    while (true)
    {
        parallelInShiftRegister::loadParallelToShiftregister();
        rsLatch::reset();
        parallelInShiftRegister::shiftOutBits(&data);

        shiftRegister::shiftInBits(&data);
        shiftRegister::showShiftRegister();
        _delay_ms(10);
    }
}
