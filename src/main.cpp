// this is only for the QtCreator to find the correct highlighting - this is already defined somewhere before
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "ArduinoDrivers/ArduinoUno.hpp"
#include "ArduinoDrivers/dummytypes.hpp"

#include "ArduinoDrivers/rslatch.hpp"
#include "ArduinoDrivers/parallelinshiftregister74hc165.hpp"
#include "ArduinoDrivers/shiftregister74hc595.hpp"

#include "ArduinoDrivers/button.hpp"
#include "ArduinoDrivers/buttonTimed.hpp"
#include "ArduinoDrivers/simplePinAvr.hpp"
#include "ArduinoDrivers/simplePinBit.hpp"

#include "helpers/crc16.hpp"

#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <string.h>


// https://stackoverflow.com/questions/6938219/how-to-check-whether-all-bytes-in-a-memory-block-are-zero
template<size_t size>
static int memvcmp(uint8_t const * memory, uint8_t const value)
{
    if (0 == size)
    {
        return 0;
    }
    else
    {
        int const firstByteComparison = memcmp(memory, &value, 1);
        return (0 == firstByteComparison) ? memcmp(memory, memory + 1, size - 1) : firstByteComparison;
    }
}



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


uint8_t incrementedLevelIndex(uint8_t const levelIndex)
{
    uint8_t modLevelIndex = levelIndex + 1;

    if (numberOfLevels == modLevelIndex)
    {
        modLevelIndex = 0;
    }

    return modLevelIndex;
}

uint8_t decrementedLevelIndex(uint8_t const levelIndex)
{
    uint8_t modLevelIndex = numberOfLevels - 1;
    if (0 != levelIndex)
    {
        modLevelIndex = levelIndex - 1;
    }

    return modLevelIndex;
}

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
    LevelSelect,
    Game,
    GameFinished
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

template<uint8_t Index>
struct WrapperCountButtonsReleasedAfterShort
{
    static_assert((matrixWidthAndHeight * matrixWidthAndHeight) > Index);

    static void impl(uint8_t & count)
    {
        if (Buttons<Index>::releasedAfterShort())
        {
            ++count;
        }
    }
};

/* Never use this for actual HW buttons - but only for the update from a level input. */
template<uint8_t Index>
struct WrapperCountButtonsPressed_
{
    static_assert((matrixWidthAndHeight * matrixWidthAndHeight) > Index);

    static void impl(uint8_t & count)
    {
        if (Button<SimplePinBitRead<Index % 8, dataIn, Index / 8>, SimplePin::State::One>::isDown())
        {
            ++count;
        }
    }
};


struct BackupValues
{
    uint8_t levelIndex;
    uint8_t dataOut[4];
    uint8_t buttonPresses;
    Mode mode;

    BackupValues(uint8_t const levelIndex_,
                 uint8_t const dataOut_[4],
                 uint8_t const buttonPresses,
                 Mode const mode)
        : levelIndex(levelIndex_)
        , buttonPresses(buttonPresses)
        , mode(mode)
    {
        memcpy(dataOut, dataOut_, sizeof(dataOut));
    }
};


namespace Eeprom
{

typedef size_t Address;

namespace Addresses
{

static Address constexpr backupValues = 0;

static_assert(E2END >= (backupValues + sizeof(BackupValues) + 2 /* CRC */ - 1 /* index */));

} // namespace Addresses


void writeWithCrc(void const * const data, size_t const byteCount, Address const eepromAddress)
{
    Crc16Ibm3740 crc;
    crc.process(static_cast<uint8_t const *>(data), byteCount);
    uint16_t const crcValue = crc.get();

    eeprom_write_block(data, (void *)(eepromAddress), byteCount);
    eeprom_write_block(&crcValue, (void *)(eepromAddress + byteCount), 2);
}


bool readWithCrc(void * const data, size_t const byteCount, Address const eepromAddress)
{
    uint16_t crcValue = 0xffff;

    eeprom_read_block(data, (void const *)(eepromAddress), byteCount);
    eeprom_read_block(&crcValue, (void const *)(eepromAddress + byteCount), 2);

    Crc16Ibm3740 crc;
    crc.process(static_cast<uint8_t const *>(data), byteCount);

    return (crc.get() == crcValue);
}


} // namespace Eeprom




typedef AvrInternalRegister<PCMSK0_REGISTER, uint8_t> PinChangeMask0;
typedef AvrInternalRegister<PCICR_REGISTER, uint8_t> PinChangeInterruptControlRegister;

// Interrupt Service Routine
ISR (PCINT0_vect)
{
    // intentionally empty - only used for wakeup.
}

void enableButtonOnOffInterrupt(bool const enable)
{
    if (enable)
    {
        // Enable pin 0 [PB0] in PCINT0.
        PinChangeMask0::setBitMask(0x01);
        // Enalbe PCINT0.
        PinChangeInterruptControlRegister::setBitMask(0x01);
        // enable interrupts
        sei();
    }
    else
    {
        // Disable pin 0 [PB0] in PCINT0.
        PinChangeMask0::clearBitMask(0x01);
        // Enalbe PCINT0.
        PinChangeInterruptControlRegister::clearBitMask(0x01);
        // disable interrupts
        cli();
    }
}

/**
 * @brief powerDown puts the microcontroller in SLEEP_MODE_PWR_SAVE.
 */
void powerDown()
{
    sleep_mode (); // here the device is actually put to sleep!!
}

/**
 * @brief powerOff puts the microcontroller in SLEEP_MODE_PWR_DOWN.
 */
void powerOff()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode (); // here the device is actually put to sleep!!
}


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
    uint8_t buttonPresses = 0;

    BackupValues backupValues(levelIndex, dataOut, buttonPresses, mode);

    bool const readBack = Eeprom::readWithCrc(&backupValues, sizeof(BackupValues), Eeprom::Addresses::backupValues);
    if (!readBack)
    {
        backupValues = BackupValues(levelIndex, dataOut, buttonPresses, mode);
        initializeDataOutToLevel(levelIndex);
    }
    else
    {
        levelIndex = backupValues.levelIndex;
        buttonPresses = backupValues.buttonPresses;
        memcpy(dataOut, backupValues.dataOut, 4);
        mode = backupValues.mode;
    }

    // In case the OnOff button is turned to off during power-up, check until
    // isUpLong() becomes true. This is so that the LEDs won't light up until
    // the long-term button state is determined.
    while (ButtonOnOff::isUp() && !ButtonOnOff::isUpLong())
    {
        ButtonOnOff::update();
    }

    while (true)
    {
        ButtonOnOff::update();

        if (ButtonOnOff::isUpLong())
        {
            backupValues = BackupValues(levelIndex, dataOut, buttonPresses, mode);

            Eeprom::writeWithCrc(&backupValues, sizeof(BackupValues), Eeprom::Addresses::backupValues);

            // turn off display
            clearDataOut();
            displayDataOut();

            enableButtonOnOffInterrupt(true);
            powerOff();
            enableButtonOnOffInterrupt(false);


            bool const readBack = Eeprom::readWithCrc(&backupValues, sizeof(BackupValues), Eeprom::Addresses::backupValues);
            if (!readBack)
            {
                mode = Mode::Game;
                levelIndex = 0;
                buttonPresses = 0;
                initializeDataOutToLevel(levelIndex);
                backupValues = BackupValues(levelIndex, dataOut, buttonPresses, mode);
            }
            else
            {
                // restore
                levelIndex = backupValues.levelIndex;
                buttonPresses = backupValues.buttonPresses;
                memcpy(dataOut, backupValues.dataOut, 4);
                mode = backupValues.mode;
            }
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
        case Mode::LevelSelect:
        {
            if (ButtonUp::releasedAfterShort())
            {
                levelIndex = incrementedLevelIndex(levelIndex);
            }
            if (ButtonDown::releasedAfterShort())
            {
                levelIndex = decrementedLevelIndex(levelIndex);
            }

            if (ButtonEnter::releasedAfterShort())
            {
                mode = Mode::Game;
                initializeDataOutToLevel(levelIndex);
                buttonPresses = 0;
            }
            else if (ButtonEscapeReset::releasedAfterShort())
            {
                memcpy(dataOut, backupValues.dataOut, 4);
                levelIndex = backupValues.levelIndex;
                buttonPresses = backupValues.buttonPresses;
                mode = Mode::Game;
            }
            else
            {
                // Update level selection display.
                memcpy(dataOut, digits[levelIndex % 0x10], 3);
                Loop<4, WrapperLedLevelsUpdate, uint8_t>::impl(levelIndex);
            }

            break;
        }
        case Mode::Game:
        {
            if (ButtonMenu::isDownLong())
            {
                mode = Mode::LevelSelect;
                backupValues = BackupValues(levelIndex, dataOut, buttonPresses, mode);
                clearDataOut();
            }
            else if (ButtonEscapeReset::isDownLong())
            {
                initializeDataOutToLevel(levelIndex);
                buttonPresses = 0;
            }
            else
            {
                uint8_t pressedButtonsCount = 0;
                Loop<24, WrapperCountButtonsReleasedAfterShort, uint8_t &>::impl(pressedButtonsCount);

                // Only update if any button pressed.
                if (0 < pressedButtonsCount)
                {
                    // Don't overflow but top off at UINT8_MAX.
                    if ((UINT8_MAX - buttonPresses) >= pressedButtonsCount)
                    {
                        buttonPresses += pressedButtonsCount;
                    }
                    else
                    {
                        buttonPresses = UINT8_MAX;
                    }


                    Loop<24, WrapperToggleNeighborReleasedAfterShort>::impl();

                    if (0 == memvcmp<4>(dataOut, 0))
                    {
                        mode = Mode::GameFinished;
                    }
                }
            }
            break;
        }
        case Mode::GameFinished:
        {
            if (ButtonMenu::releasedAfterShort() || ButtonMenu::isDownLong())
            {
                // open menu
                initializeDataOutToLevel(levelIndex);
                backupValues = BackupValues(levelIndex, dataOut, 0, mode);
                clearDataOut();
                mode = Mode::LevelSelect;
            }
            else if (ButtonEscapeReset::releasedAfterShort() || ButtonEscapeReset::isDownLong())
            {
                // restart level
                initializeDataOutToLevel(levelIndex);
                buttonPresses = 0;
                mode = Mode::Game;
            }
            else if (ButtonEnter::releasedAfterShort() || ButtonEnter::isDownLong())
            {
                // advance to next level
                levelIndex = incrementedLevelIndex(levelIndex);
                initializeDataOutToLevel(levelIndex);
                buttonPresses = 0;
                mode = Mode::Game;
            }
            else
            {
                // show the number of superfluous button presses
                memcpy(dataIn, levels[levelIndex], sizeof(dataIn)); // misuse dataIn - it will be overwritten on next read-in from HW
                uint8_t pressedButtonsCountForLevel = 0;
                Loop<24, WrapperCountButtonsPressed_, uint8_t &>::impl(pressedButtonsCountForLevel);

                uint8_t const buttonPressesDelta = buttonPresses - pressedButtonsCountForLevel;
                // Update level selection display.
                memcpy(dataOut, digits[buttonPressesDelta % 0x10], 3);
                Loop<4, WrapperLedLevelsUpdate, uint8_t>::impl(buttonPressesDelta);

                Leds<14>::set(SimpleOnOffProperties::State::On);
            }
            break;
        }
        }

        displayDataOut();

        // Wait some time as to not pull/push the shift-registers too often.
        _delay_ms(100);
    }
}
