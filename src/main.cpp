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
    VccPeriphery::setType(AvrInputOutput::OutputLow);

    typedef RsLatch<DummyAvrPin1, arduinoUno::pinC1, DummyAvrPin1> buttonsInLatcher;
    buttonsInLatcher::initialize();

    typedef ParallelInShiftRegister74HC165<32,
            arduinoUno::pinC3,
            arduinoUno::pinC2,
            DummyAvrPin1,
            arduinoUno::pinC4,
            DummyAvrPin1,
            DummyAvrPin1> buttonsInShiftRegister;
    buttonsInShiftRegister::initialize();

    typedef ShiftRegister74HC595<32,
            arduinoUno::pinD2,
            arduinoUno::pinD5,
            arduinoUno::pinD4,
            arduinoUno::pinD3,
            arduinoUno::pinD6> ledsOutShiftRegister;
    ledsOutShiftRegister::initialize();


    buttonsInShiftRegister::enableClock();
    ledsOutShiftRegister::enableOutput();
    buttonsInLatcher::reset();

    uint8_t data[4] = {0x01, 0x00, 0x00, 0x00};

    while (true)
    {
        // Latch bits in shift-register for read-out from the buttons.
        buttonsInShiftRegister::loadParallelToShiftregister();
        // Reset latches in front of read-out-shiftregisters.
        buttonsInLatcher::reset();
        // Actually copy the latched shift-register values to data.
        buttonsInShiftRegister::shiftOutBits(data);

        // Move data to the LED shiftRegister.
        ledsOutShiftRegister::shiftInBits(data);
        // Apply the shifted-in bits to the output of the shift-registers.
        ledsOutShiftRegister::showShiftRegister();

        _delay_ms(10);
    }
}
