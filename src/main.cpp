// this is only for the QtCreator to find the correct highlighting - this is already defined somewhere before
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "ArduinoDrivers/ArduinoUno.hpp"
#include "ArduinoDrivers/dummytypes.hpp"

#include "ArduinoDrivers/rslatch.hpp"
#include "ArduinoDrivers/parallelinshiftregister74hc165.hpp"
#include "ArduinoDrivers/shiftregister74hc595.hpp"

#include "ArduinoDrivers/button.hpp"
#include "ArduinoDrivers/buttonTimed.hpp"
#include "ArduinoDrivers/simplePinAvr.hpp"
#include "ArduinoDrivers/simplePinBit.hpp"

#include <string.h>

static uint8_t constexpr matrixWidthAndHeight = 5;

typedef RsLatch<DummyAvrPin1, ArduinoUno::pinC1, DummyAvrPin1> buttonsInLatcher;

uint8_t constexpr shiftRegisterBitsCount = 32;
static_assert(shiftRegisterBitsCount >= (matrixWidthAndHeight * matrixWidthAndHeight));

typedef ParallelInShiftRegister74HC165<shiftRegisterBitsCount,
                                       ArduinoUno::pinC3,
                                       ArduinoUno::pinC2,
                                       DummyAvrPin1,
                                       ArduinoUno::pinC4,
                                       DummyAvrPin1,
                                       DummyAvrPin1> buttonsInShiftRegister;

typedef ShiftRegister74HC595<shiftRegisterBitsCount,
                             ArduinoUno::pinD2,
                             ArduinoUno::pinD5,
                             ArduinoUno::pinD4,
                             ArduinoUno::pinD3,
                             ArduinoUno::pinD6> ledsOutShiftRegister;

uint8_t constexpr shortPressCount = 2;
uint8_t constexpr longPressCount = 8;

typedef ButtonTimed<Button<SimplePinAvrRead<ArduinoUno::D8, AvrInputOutput::InputPullup>, SimplePin::State::Zero>, shortPressCount, longPressCount> ButtonOnOff;

static uint8_t dataIn[4] = {0x00, 0x00, 0x00, 0x00};
static uint8_t dataOut[4] = {0x00, 0x00, 0x00, 0x00};

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
    {0b10000111, 0b00011000, 0b01110010, }, // E
    {0b10000100, 0b00011100, 0b01110010, }, // F
};

uint8_t constexpr levels[][4] = {
    {0b00000000, 0b00010000, 0b00000000, 0b00000000},
    {0b00010001, 0b00000000, 0b00010000, 0b00000001},
    {0b01000000, 0b00010000, 0b00000100, 0b00000000},
//    {0b, 0b, 0b, 0b},
};
uint8_t constexpr numberOfLevels = sizeof(levels) / sizeof(levels[0]);

// Template-Meta-Programming loop
template<uint8_t Index, template<uint8_t I> class Wrapper, typename... Args>
struct Loop
{
    static void impl(Args... args)
    {
        //Execute some code
        Wrapper<Index>::impl(args...);

        //Recurse
        Loop<Index - 1, Wrapper, Args...>::impl(args...);
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

/* Never use this for actual HW buttons - but only for the update from a level input. */
template<uint8_t Index>
struct WrapperToggleNeighborIsDown
{
    static_assert((matrixWidthAndHeight * matrixWidthAndHeight) > Index);

    static void impl()
    {
        if (Button<SimplePinBitRead<Index % 8, dataIn, Index / 8>, SimplePin::State::One>::isDown())
        {
            ToggleNeighbor<true, Index>::impl();
            ToggleNeighbor<(0 != (Index % matrixWidthAndHeight)), static_cast<uint8_t>(Index - 1)>::impl();
            ToggleNeighbor<((matrixWidthAndHeight - 1) != (Index % matrixWidthAndHeight)), (Index + 1)>::impl();
            ToggleNeighbor<(matrixWidthAndHeight <= Index), static_cast<uint8_t>(Index - matrixWidthAndHeight)>::impl();
            ToggleNeighbor<((matrixWidthAndHeight * (matrixWidthAndHeight - 1)) > Index), static_cast<uint8_t>(Index + matrixWidthAndHeight)>::impl();
        }
    }
};

static void initializeDataOutToLevel(uint8_t const levelIndex)
{
    static_assert(sizeof(dataIn) == sizeof(levels[0]));
    memcpy(dataIn, levels[levelIndex], sizeof(dataIn));
    memset(dataOut, 0, sizeof(dataOut));
    Loop<24, WrapperToggleNeighborIsDown>::impl();
}

static void clearDataOut()
{
    memset(dataOut, 0, sizeof(dataOut));
}

static void displayDataOut()
{
    // Move data to the LED shiftRegister.
    ledsOutShiftRegister::shiftInBits(dataOut);
    // Apply the shifted-in bits to the output of the shift-registers.
    ledsOutShiftRegister::showShiftRegister();
}

enum class Mode
{
    Game,
    LevelSelect
};

typedef Buttons< 24> ButtonMenu;
typedef Buttons< 4> ButtonEscapeReset;
typedef Buttons<19> ButtonUp;
typedef Buttons< 9> ButtonDown;
typedef Buttons<14> ButtonEnter;


template <uint8_t index>
class LedLevels;

template <> class LedLevels<0> : public Leds<3> {};
template <> class LedLevels<1> : public Leds<8> {};
template <> class LedLevels<2> : public Leds<13> {};
template <> class LedLevels<3> : public Leds<18> {};
template <> class LedLevels<4> : public Leds<23> {};

template<uint8_t Index>
struct WrapperLedLevelsUpdate
{
    static_assert(matrixWidthAndHeight > Index);

    static void impl(uint8_t const levelIndex)
    {
        if (Index <= (levelIndex / 0x10))
        {
            LedLevels<Index>::set(SimpleOnOffProperties::State::On);
        }
        else
        {
            LedLevels<Index>::set(SimpleOnOffProperties::State::Off);
        }
    }
};


struct BackupValues
{
    uint8_t levelIndex;
    uint8_t dataOut[4];

    BackupValues(uint8_t const levelIndex_, uint8_t const dataOut_[4])
        : levelIndex(levelIndex_)
    {
        memcpy(dataOut, dataOut_, sizeof(dataOut));
    }
};

int main()
{
    typedef ArduinoUno::pinC5 VccPeriphery;
    VccPeriphery::setType(AvrInputOutput::OutputLow);

    buttonsInLatcher::initialize();
    buttonsInShiftRegister::initialize();
    ledsOutShiftRegister::initialize();


    buttonsInShiftRegister::enableClock();
    ledsOutShiftRegister::enableOutput();
    buttonsInLatcher::reset();

    Loop<24, WrapperInitialize>::impl();

    ButtonOnOff::initialize();

    // todo: save/load
    Mode mode = Mode::Game;
    uint8_t levelIndex = 0;

    BackupValues backupValues(levelIndex, dataOut);


    initializeDataOutToLevel(levelIndex);

    while (true)
    {
        ButtonOnOff::update();

        if (ButtonOnOff::isUpLong())
        {
            backupValues = BackupValues(levelIndex, dataOut);

            // turn off display
            clearDataOut();
            displayDataOut();

            while (ButtonOnOff::isUpLong())
            {
                // Todo: make the AVR sleep.
                ButtonOnOff::update();
            }

            // restore display
            memcpy(dataOut, backupValues.dataOut, 4);
        }


        // Latch bits in shift-register for read-out from the buttons.
        buttonsInShiftRegister::loadParallelToShiftregister();
        // Reset latches in front of read-out-shiftregisters.
        buttonsInLatcher::reset();
        // Actually copy the latched shift-register values to data.
        buttonsInShiftRegister::shiftOutBits(dataIn);

        Loop<24, WrapperUpdate>::impl();

        switch (mode)
        {
        case Mode::Game:
        {
            if (ButtonMenu::isDownLong())
            {
                mode = Mode::LevelSelect;
                backupValues = BackupValues(levelIndex, dataOut);
                clearDataOut();
            }
            else if (ButtonEscapeReset::isDownLong())
            {
                initializeDataOutToLevel(levelIndex);
            }
            else
            {
                Loop<24, WrapperToggleNeighborReleasedAfterShort>::impl();
            }
            break;
        }
        case Mode::LevelSelect:
        {
            if (ButtonUp::releasedAfterShort())
            {
                ++levelIndex;

                if (numberOfLevels == levelIndex)
                {
                    levelIndex = 0;
                }
            }
            if (ButtonDown::releasedAfterShort())
            {
                if (0 == levelIndex)
                {
                    levelIndex = numberOfLevels - 1;
                }
                else
                {
                    --levelIndex;
                }
            }

            if (ButtonEnter::releasedAfterShort())
            {
                mode = Mode::Game;
                initializeDataOutToLevel(levelIndex);
            }
            else if (ButtonEscapeReset::releasedAfterShort())
            {
                memcpy(dataOut, backupValues.dataOut, 4);
                levelIndex = backupValues.levelIndex;
                mode = Mode::Game;
            }
            else
            {
                memcpy(dataOut, digits[levelIndex % 16], 3);

                Loop<4, WrapperLedLevelsUpdate, uint8_t>::impl(levelIndex);
            }

            break;
        }
        }

        displayDataOut();

        // Wait some time as to not pull/push the shift-registers too often.
        _delay_ms(100);
    }
}
