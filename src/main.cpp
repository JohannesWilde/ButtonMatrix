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

#include "ArduinoDrivers/button.hpp"
#include "ArduinoDrivers/buttonTimed.hpp"
#include "ArduinoDrivers/simplePinBit.hpp"

#include <string.h>


static uint8_t constexpr matrixWidthAndHeight = 5;

static uint8_t dataIn[4] = {0x00, 0x00, 0x00, 0x00};
static uint8_t dataOut[4] = {0x00, 0x00, 0x00, 0x00};

uint8_t constexpr shortPressCount = 2;
uint8_t constexpr longPressCount = 8;

template <uint8_t index>
class Buttons;

template <> class Buttons< 0> : public ButtonTimed<Button<SimplePinBitRead<0, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 1> : public ButtonTimed<Button<SimplePinBitRead<1, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 2> : public ButtonTimed<Button<SimplePinBitRead<2, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 3> : public ButtonTimed<Button<SimplePinBitRead<3, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 4> : public ButtonTimed<Button<SimplePinBitRead<4, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 5> : public ButtonTimed<Button<SimplePinBitRead<5, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 6> : public ButtonTimed<Button<SimplePinBitRead<6, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 7> : public ButtonTimed<Button<SimplePinBitRead<7, dataIn, 0>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 8> : public ButtonTimed<Button<SimplePinBitRead<0, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons< 9> : public ButtonTimed<Button<SimplePinBitRead<1, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<10> : public ButtonTimed<Button<SimplePinBitRead<2, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<11> : public ButtonTimed<Button<SimplePinBitRead<3, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<12> : public ButtonTimed<Button<SimplePinBitRead<4, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<13> : public ButtonTimed<Button<SimplePinBitRead<5, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<14> : public ButtonTimed<Button<SimplePinBitRead<6, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<15> : public ButtonTimed<Button<SimplePinBitRead<7, dataIn, 1>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<16> : public ButtonTimed<Button<SimplePinBitRead<0, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<17> : public ButtonTimed<Button<SimplePinBitRead<1, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<18> : public ButtonTimed<Button<SimplePinBitRead<2, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<19> : public ButtonTimed<Button<SimplePinBitRead<3, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<20> : public ButtonTimed<Button<SimplePinBitRead<4, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<21> : public ButtonTimed<Button<SimplePinBitRead<5, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<22> : public ButtonTimed<Button<SimplePinBitRead<6, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<23> : public ButtonTimed<Button<SimplePinBitRead<7, dataIn, 2>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};
template <> class Buttons<24> : public ButtonTimed<Button<SimplePinBitRead<0, dataIn, 3>, SimplePin::State::One>, shortPressCount, longPressCount> {/* intentionally empty */};


SimplePin::State constexpr ledStateOn = SimplePin::State::One;

template <uint8_t index>
class Leds;

template <> class Leds< 0> : public SimpleOnOff<SimplePinBit<0, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 1> : public SimpleOnOff<SimplePinBit<1, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 2> : public SimpleOnOff<SimplePinBit<2, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 3> : public SimpleOnOff<SimplePinBit<3, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 4> : public SimpleOnOff<SimplePinBit<4, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 5> : public SimpleOnOff<SimplePinBit<5, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 6> : public SimpleOnOff<SimplePinBit<6, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 7> : public SimpleOnOff<SimplePinBit<7, dataOut, 0>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 8> : public SimpleOnOff<SimplePinBit<0, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds< 9> : public SimpleOnOff<SimplePinBit<1, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<10> : public SimpleOnOff<SimplePinBit<2, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<11> : public SimpleOnOff<SimplePinBit<3, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<12> : public SimpleOnOff<SimplePinBit<4, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<13> : public SimpleOnOff<SimplePinBit<5, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<14> : public SimpleOnOff<SimplePinBit<6, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<15> : public SimpleOnOff<SimplePinBit<7, dataOut, 1>, ledStateOn> {/* intentionally empty */};
template <> class Leds<16> : public SimpleOnOff<SimplePinBit<0, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<17> : public SimpleOnOff<SimplePinBit<1, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<18> : public SimpleOnOff<SimplePinBit<2, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<19> : public SimpleOnOff<SimplePinBit<3, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<20> : public SimpleOnOff<SimplePinBit<4, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<21> : public SimpleOnOff<SimplePinBit<5, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<22> : public SimpleOnOff<SimplePinBit<6, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<23> : public SimpleOnOff<SimplePinBit<7, dataOut, 2>, ledStateOn> {/* intentionally empty */};
template <> class Leds<24> : public SimpleOnOff<SimplePinBit<0, dataOut, 3>, ledStateOn> {/* intentionally empty */};


static uint8_t constexpr digits[16][3] = {
    {0b10100111, 0b10010100, 0b01110010, }, // 0
    {0b00100001, 0b10010100, 0b00010001, }, // 1
    {0b10000111, 0b10011100, 0b01110000, }, // 2
    {0b00100111, 0b10001100, 0b01110000, }, // 3
    {0b00100001, 0b10011100, 0b01010010, }, // 4
    {0b00100111, 0b00011100, 0b01110010, }, // 5
    {0b10100111, 0b00011100, 0b01110010, }, // 6
    {0b10000100, 0b10001000, 0b01110000, }, // 7
    {0b10100111, 0b10011100, 0b01110010, }, // 8
    {0b00100111, 0b10011100, 0b01110010, }, // 9
    {0b10100101, 0b10011100, 0b01110010, }, // A
    {0b10100111, 0b00011100, 0b01000010, }, // b
    {0b10000111, 0b00010000, 0b01110010, }, // C
    {0b10100111, 0b10011100, 0b00010000, }, // d
    {0b10000111, 0b00011100, 0b01110010, }, // E
    {0b10000100, 0b00011100, 0b01110010, }, // F
};


// Template-Meta-Programming loop
template<uint8_t Index, template<uint8_t I> class Wrapper, typename... Args>
struct Loop
{
    static void impl(Args... args)
    {
        //Execute some code
        Wrapper<Index>::impl(args...);

        //Recurse
        Loop<Index - 1, Wrapper>::impl();
    }
};

// Loop end specialization.
template<template<uint8_t I> class Wrapper, typename... Args>
struct Loop<0, Wrapper, Args...>
{
    static void impl(Args... args)
    {
        //Execute some code
        Wrapper<0>::impl(args...);
    }
};

// Wrappers for loops.
template<uint8_t Index>
struct WrapperInitialize
{
    static void impl()
    {
        Buttons<Index>::initialize();
        Leds<Index>::initialize();
    }
};


template<uint8_t Index>
struct WrapperDeinitialize
{
    static void impl()
    {
        Buttons<Index>::deinitialize();
        Leds<Index>::deinitialize();
    }
};


template<uint8_t Index>
struct WrapperUpdate
{
    static void impl()
    {
        Buttons<Index>::update();
    }
};




template<bool condition, uint8_t NeighborIndex>
struct ToggleNeighbor
{
    static void impl();
};

template<uint8_t NeighborIndex>
struct ToggleNeighbor<true, NeighborIndex>
{
    static void impl()
    {
        Leds<NeighborIndex>::toggle();
    }
};

template<uint8_t NeighborIndex>
struct ToggleNeighbor<false, NeighborIndex>
{
    static void impl()
    {
        // intentionally empty
    }
};

template<uint8_t Index>
struct WrapperToggleNeighborReleasedAfterShort
{
    static void impl()
    {
        if (Buttons<Index>::releasedAfterShort())
        {
            ToggleNeighbor<true, Index>::impl();
            ToggleNeighbor<(0 != (Index % matrixWidthAndHeight)), static_cast<uint8_t>(Index - 1)>::impl();
            ToggleNeighbor<((matrixWidthAndHeight - 1) != (Index % matrixWidthAndHeight)), (Index + 1)>::impl();
            ToggleNeighbor<(matrixWidthAndHeight <= Index), static_cast<uint8_t>(Index - matrixWidthAndHeight)>::impl();
            ToggleNeighbor<((matrixWidthAndHeight * (matrixWidthAndHeight - 1)) > Index), static_cast<uint8_t>(Index + matrixWidthAndHeight)>::impl();
        }
    }
};


int main()
{
    typedef ArduinoUno arduinoUno;

    typedef arduinoUno::pinC5 VccPeriphery;
    VccPeriphery::setType(AvrInputOutput::OutputLow);

    typedef RsLatch<DummyAvrPin1, arduinoUno::pinC1, DummyAvrPin1> buttonsInLatcher;
    buttonsInLatcher::initialize();

    uint8_t constexpr shiftRegisterBitsCount = 32;
    static_assert(shiftRegisterBitsCount >= (matrixWidthAndHeight * matrixWidthAndHeight));

    typedef ParallelInShiftRegister74HC165<shiftRegisterBitsCount,
            arduinoUno::pinC3,
            arduinoUno::pinC2,
            DummyAvrPin1,
            arduinoUno::pinC4,
            DummyAvrPin1,
            DummyAvrPin1> buttonsInShiftRegister;
    buttonsInShiftRegister::initialize();

    typedef ShiftRegister74HC595<shiftRegisterBitsCount,
            arduinoUno::pinD2,
            arduinoUno::pinD5,
            arduinoUno::pinD4,
            arduinoUno::pinD3,
            arduinoUno::pinD6> ledsOutShiftRegister;
    ledsOutShiftRegister::initialize();


    buttonsInShiftRegister::enableClock();
    ledsOutShiftRegister::enableOutput();
    buttonsInLatcher::reset();

    Loop<24, WrapperInitialize>::impl();

//    while (true)
//    {
//        // Latch bits in shift-register for read-out from the buttons.
//        buttonsInShiftRegister::loadParallelToShiftregister();
//        // Reset latches in front of read-out-shiftregisters.
//        buttonsInLatcher::reset();
//        // Actually copy the latched shift-register values to data.
//        buttonsInShiftRegister::shiftOutBits(dataIn);

//        Loop<24, WrapperUpdate>::impl();
//        Loop<24, WrapperToggleNeighborReleasedAfterShort>::impl();

//        // Move data to the LED shiftRegister.
//        ledsOutShiftRegister::shiftInBits(dataOut);
//        // Apply the shifted-in bits to the output of the shift-registers.
//        ledsOutShiftRegister::showShiftRegister();

//        // Wait some time as to not pull/push the shift-registers too often.
//        _delay_ms(100);
//    }

    uint8_t index = 0;
    while (true)
    {
        memcpy(dataOut, digits[index], 3);
        index = ((index + 1) % (sizeof(digits) / sizeof(digits[0])));

        // Move data to the LED shiftRegister.
        ledsOutShiftRegister::shiftInBits(dataOut);
        // Apply the shifted-in bits to the output of the shift-registers.
        ledsOutShiftRegister::showShiftRegister();

        // Wait some time as to not pull/push the shift-registers too often.
        _delay_ms(1000);
    }
}
