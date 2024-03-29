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
#include <avr/pgmspace.h>
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

uint8_t incrementUint8Capped(uint8_t const value)
{
    uint8_t newValue = value;
    if (newValue < UCHAR_MAX)
    {
        ++newValue;
    }
    return newValue;
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


static uint8_t constexpr digits[16][3] PROGMEM = {
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

static void readSingleDigitToDataOut(uint8_t const digit)
{
    uint8_t const singleDigit = digit % 0x10;

    // Read level button presses to dataIn.
    for (size_t index = 0; index < 3; ++index)
    {
        dataOut[index] = pgm_read_byte_near(digits[singleDigit] + index);
    }
}

// Freely taken from https://1lights.thebluesky.net/ - private use only.
//        __________________
//        | 24 23 22 21 20 |
//        | 19 18 17 16 15 |
//        | 14 13 12 11 10 |
//        |  9  8  7  6  5 |
// 0/1 -> |  4  3  2  1  0 |
//        ------------   ---
//                    USB
// corresponds to
//
// { 0b 7 6 5 4 3 2 1 0, 0b 15 14 13 12 11 10 9 8, 0b 23 22 21 20 19 18 17 16, 0b 31 30 29 28 27 26 25 24 }
//

template <size_t byteOffset, size_t index, size_t... indices>
static constexpr uint8_t createBitmaskToPress();

template <size_t byteOffset>
static constexpr uint8_t createBitmaskToPress()
{
    return 0;
}

template <size_t byteOffset, size_t index, size_t... indices>
static constexpr uint8_t createBitmaskToPress()
{
    uint8_t value = 0;
    size_t const byteIndex = index / CHAR_BIT;

    static_assert(byteOffset == byteIndex);

    size_t const bitIndex = index % CHAR_BIT;
    value |= (0b1 << bitIndex);

    value |= createBitmaskToPress<byteOffset, indices...>();
    return value;
}

static uint8_t constexpr levels[][4] PROGMEM = {
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()}, // 0x00, beginner
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 10, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 13, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4>(), createBitmaskToPress<1>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 4>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12, 13>(), createBitmaskToPress<2, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 7>(), createBitmaskToPress<1, 11>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()}, // 0x10
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 9, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 10, 12>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 8>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 18, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 6>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 12, 14>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 19>(), createBitmaskToPress<3>()}, // 0x20
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 5>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 4>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 10, 11, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5, 6, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1, 8, 13>(), createBitmaskToPress<2, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 7>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 17, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4>(), createBitmaskToPress<1, 14, 15>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 4>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 16, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 9, 11, 13>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()}, // 0x30
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 9, 11, 13>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 9, 11>(), createBitmaskToPress<2, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 3>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 10, 15>(), createBitmaskToPress<2, 17, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 6>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 11, 14, 15>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 6, 7>(), createBitmaskToPress<1, 12, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 7>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 21, 22>(), createBitmaskToPress<3, 24>()}, // intermediate
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 17, 18, 20, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 18>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 10, 12, 15>(), createBitmaskToPress<2, 20, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 9, 10, 12>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 9, 11, 12, 14>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 5, 6>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 16, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3>()}, // 0x40
    {createBitmaskToPress<0, 2, 4, 5, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 10, 13>(), createBitmaskToPress<2, 18, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 5, 7>(), createBitmaskToPress<1, 12, 15>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 7>(), createBitmaskToPress<1, 12, 15>(), createBitmaskToPress<2, 18, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 19, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2, 6, 7>(), createBitmaskToPress<1, 8, 14>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 13, 14>(), createBitmaskToPress<2, 17, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18, 19, 20, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1, 8, 10, 15>(), createBitmaskToPress<2, 17, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 17, 18, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 6>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 4>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 10, 14>(), createBitmaskToPress<2, 16, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 8, 13>(), createBitmaskToPress<2, 16, 21, 22>(), createBitmaskToPress<3>()}, // 0x50
    {createBitmaskToPress<0, 1, 2>(), createBitmaskToPress<1, 8, 11, 12>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 3, 7>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 16, 17, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 3, 4, 7>(), createBitmaskToPress<1, 8, 13>(), createBitmaskToPress<2, 17, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 6>(), createBitmaskToPress<1, 14, 15>(), createBitmaskToPress<2, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 7>(), createBitmaskToPress<1, 8, 10, 13, 14>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2, 7>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 17, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 3, 6>(), createBitmaskToPress<1, 10, 11, 12>(), createBitmaskToPress<2, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5, 6>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 10, 13, 14>(), createBitmaskToPress<2, 18, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 5>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 16, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 5>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 16, 19, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4>(), createBitmaskToPress<1, 8, 11>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 5, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3, 24>()}, // 0x60
    {createBitmaskToPress<0, 4>(), createBitmaskToPress<1, 8, 9, 13>(), createBitmaskToPress<2, 16, 17, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 4, 5, 6, 7>(), createBitmaskToPress<1, 10, 11>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 7>(), createBitmaskToPress<1, 8, 13>(), createBitmaskToPress<2, 19, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 14, 15>(), createBitmaskToPress<2, 18, 19, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 3>(), createBitmaskToPress<1, 8, 10>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4, 7>(), createBitmaskToPress<1, 10, 14>(), createBitmaskToPress<2, 17, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 7>(), createBitmaskToPress<1, 11>(), createBitmaskToPress<2, 17, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2, 7>(), createBitmaskToPress<1, 9, 12, 13, 15>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 9, 10, 12, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 3>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2, 16, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 6>(), createBitmaskToPress<1, 13, 14>(), createBitmaskToPress<2, 16, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 3>(), createBitmaskToPress<1, 8>(), createBitmaskToPress<2, 16, 17, 20, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 15>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 8, 11, 12>(), createBitmaskToPress<2, 19, 20, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 3, 7>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 17, 18, 19, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 7>(), createBitmaskToPress<1, 8, 10, 13>(), createBitmaskToPress<2, 19, 20>(), createBitmaskToPress<3>()}, // 0x70
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 9, 10, 14>(), createBitmaskToPress<2, 17, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 6, 7>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 19, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 4, 7>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 19, 20, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 5, 6, 7>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 4>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 17, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 5>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 17, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 6>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 16, 18, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 7>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2, 16, 17, 19, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 5, 6>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 16, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 5>(), createBitmaskToPress<1, 10, 15>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 5>(), createBitmaskToPress<1, 8, 13, 14, 15>(), createBitmaskToPress<2, 16, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 6>(), createBitmaskToPress<1, 8, 14>(), createBitmaskToPress<2, 16, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 3, 5>(), createBitmaskToPress<1, 10, 12, 14>(), createBitmaskToPress<2, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 8, 10, 11, 12, 13>(), createBitmaskToPress<2, 17>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 5, 7>(), createBitmaskToPress<1, 9, 12>(), createBitmaskToPress<2, 18, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2, 4, 6, 7>(), createBitmaskToPress<1, 8, 10, 11>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()}, // 0x80
    {createBitmaskToPress<0, 0, 3, 4>(), createBitmaskToPress<1, 9, 10, 12, 14>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 3, 4, 7>(), createBitmaskToPress<1, 8>(), createBitmaskToPress<2, 17, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 3, 5>(), createBitmaskToPress<1, 11, 12, 15>(), createBitmaskToPress<2, 17, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 10, 12, 15>(), createBitmaskToPress<2, 16, 17, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 5, 6, 7>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 16, 20, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 5, 7>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 16, 18, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 6>(), createBitmaskToPress<1, 8, 13, 14>(), createBitmaskToPress<2, 16, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 3, 4, 7>(), createBitmaskToPress<1, 14, 15>(), createBitmaskToPress<2, 16, 17, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3, 4, 7>(), createBitmaskToPress<1, 8>(), createBitmaskToPress<2, 18, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4, 7>(), createBitmaskToPress<1, 9, 11>(), createBitmaskToPress<2, 17, 18, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 4, 7>(), createBitmaskToPress<1, 8, 10, 11, 12, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 6>(), createBitmaskToPress<1, 12, 13, 15>(), createBitmaskToPress<2, 18, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3>(), createBitmaskToPress<1, 8, 9, 10, 11, 12>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 2, 3, 6>(), createBitmaskToPress<1, 9, 10, 12, 13>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3>(), createBitmaskToPress<1, 9, 12, 14>(), createBitmaskToPress<2, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 3, 5, 7>(), createBitmaskToPress<1, 10, 11>(), createBitmaskToPress<2, 16, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 6>(), createBitmaskToPress<1, 9, 10, 15>(), createBitmaskToPress<2, 17, 18, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 5>(), createBitmaskToPress<1, 9, 10, 11>(), createBitmaskToPress<2, 17, 18, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 6>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 16, 19, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 4, 5>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 18, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4, 6, 7>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 16, 17, 19, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 5, 7>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 8, 9, 14>(), createBitmaskToPress<2, 16, 17, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 5, 7>(), createBitmaskToPress<1, 13, 15>(), createBitmaskToPress<2, 20, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 5, 7>(), createBitmaskToPress<1, 8, 11, 14, 15>(), createBitmaskToPress<2, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 5, 6>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 17, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 3, 5>(), createBitmaskToPress<1, 8, 11>(), createBitmaskToPress<2, 17, 19, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 3>(), createBitmaskToPress<1, 10, 11, 14, 15>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 6, 7>(), createBitmaskToPress<1, 9, 14>(), createBitmaskToPress<2, 16, 17, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 16, 18, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 19, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 7>(), createBitmaskToPress<1, 8, 11, 12, 13>(), createBitmaskToPress<2, 16, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 5, 6>(), createBitmaskToPress<1, 9, 12, 13, 14>(), createBitmaskToPress<2, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 4, 5>(), createBitmaskToPress<1, 8, 9, 13>(), createBitmaskToPress<2, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 5>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 19, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 5, 6, 7>(), createBitmaskToPress<1, 8, 10, 15>(), createBitmaskToPress<2, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5>(), createBitmaskToPress<1, 8, 9, 10, 13>(), createBitmaskToPress<2, 17, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 6>(), createBitmaskToPress<1, 11, 14>(), createBitmaskToPress<2, 17, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 5>(), createBitmaskToPress<1, 8, 10, 11, 12, 13, 14, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 5>(), createBitmaskToPress<1, 12, 13, 15>(), createBitmaskToPress<2, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 7>(), createBitmaskToPress<1, 8, 10, 13, 15>(), createBitmaskToPress<2, 17, 19, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 4, 7>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 16, 20, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 9, 10, 13, 15>(), createBitmaskToPress<2, 16, 17, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4, 6>(), createBitmaskToPress<1, 8, 9, 13>(), createBitmaskToPress<2, 16, 17, 18, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 6, 7>(), createBitmaskToPress<1, 9, 14>(), createBitmaskToPress<2, 16, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4>(), createBitmaskToPress<1, 8, 9>(), createBitmaskToPress<2, 16, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 7>(), createBitmaskToPress<1, 10, 12, 13, 15>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4, 7>(), createBitmaskToPress<1, 12, 13, 14, 15>(), createBitmaskToPress<2, 16, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4>(), createBitmaskToPress<1, 12, 15>(), createBitmaskToPress<2, 17, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 4, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 5>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 17, 19, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 4, 6>(), createBitmaskToPress<1, 9, 10>(), createBitmaskToPress<2, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 11, 14>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 7>(), createBitmaskToPress<1, 9, 11, 14>(), createBitmaskToPress<2, 18, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 6>(), createBitmaskToPress<1, 8, 10, 11, 12, 15>(), createBitmaskToPress<2, 17, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5>(), createBitmaskToPress<1, 10, 12, 14, 15>(), createBitmaskToPress<2, 17, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 3, 6>(), createBitmaskToPress<1, 8, 9, 11, 12, 14>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 5>(), createBitmaskToPress<1, 9, 13, 14>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 3, 5, 6>(), createBitmaskToPress<1, 9, 10, 12>(), createBitmaskToPress<2, 16, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 6>(), createBitmaskToPress<1, 8, 10, 12, 13>(), createBitmaskToPress<2, 16, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 6, 7>(), createBitmaskToPress<1, 9, 12>(), createBitmaskToPress<2, 16, 17, 18, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 5>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 16, 17, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 7>(), createBitmaskToPress<1, 9, 10, 11, 12>(), createBitmaskToPress<2, 16, 17, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 7>(), createBitmaskToPress<1, 8, 11, 13, 15>(), createBitmaskToPress<2, 17, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 6, 7>(), createBitmaskToPress<1, 10, 13, 15>(), createBitmaskToPress<2, 17, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 3, 5, 6, 7>(), createBitmaskToPress<1, 8, 9, 12>(), createBitmaskToPress<2, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 4, 5, 6>(), createBitmaskToPress<1, 8, 11, 12>(), createBitmaskToPress<2, 16, 18, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 6>(), createBitmaskToPress<1, 8, 10, 11, 12, 14>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5>(), createBitmaskToPress<1, 8, 9, 10, 12, 13>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 3, 4, 6>(), createBitmaskToPress<1, 9, 12>(), createBitmaskToPress<2, 16, 18, 19, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4>(), createBitmaskToPress<1, 8, 9, 11, 12, 13>(), createBitmaskToPress<2, 19, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1, 10, 11, 12, 15>(), createBitmaskToPress<2, 16, 19, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 6>(), createBitmaskToPress<1, 8, 10, 12>(), createBitmaskToPress<2, 16, 18, 20, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 17, 19, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 5, 6>(), createBitmaskToPress<1, 8, 12, 15>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 3, 4, 5>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 16, 18, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1, 9, 12, 14>(), createBitmaskToPress<2, 16, 18, 19, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 7>(), createBitmaskToPress<1, 8, 9, 10, 12, 13>(), createBitmaskToPress<2, 16, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14, 15>(), createBitmaskToPress<2, 17, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4>(), createBitmaskToPress<1, 8, 10, 12>(), createBitmaskToPress<2, 16, 18, 20, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 6, 7>(), createBitmaskToPress<1, 9, 11, 12, 15>(), createBitmaskToPress<2, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 5>(), createBitmaskToPress<1, 8, 10, 11, 15>(), createBitmaskToPress<2, 18, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 6>(), createBitmaskToPress<1, 9, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 7>(), createBitmaskToPress<1, 8, 10, 13, 14, 15>(), createBitmaskToPress<2, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 16, 17, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 5, 6, 7>(), createBitmaskToPress<1, 10, 14, 15>(), createBitmaskToPress<2, 16, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 5, 7>(), createBitmaskToPress<1, 10, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 21, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 6, 7>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 16, 17, 18, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 11, 12>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 15>(), createBitmaskToPress<2, 16, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 6>(), createBitmaskToPress<1, 8, 10>(), createBitmaskToPress<2, 16, 18, 19, 20, 21, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 8, 13, 14, 15>(), createBitmaskToPress<2, 18, 19, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 6>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 18, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 3, 6>(), createBitmaskToPress<1, 11, 12, 15>(), createBitmaskToPress<2, 18, 19, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 3>(), createBitmaskToPress<1, 8, 9, 10, 11, 12, 15>(), createBitmaskToPress<2, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3, 6>(), createBitmaskToPress<1, 8, 9, 10, 11, 12>(), createBitmaskToPress<2, 17, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4>(), createBitmaskToPress<1, 9, 12>(), createBitmaskToPress<2, 16, 17, 18, 19, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 13, 14, 15>(), createBitmaskToPress<2, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 4, 6>(), createBitmaskToPress<1, 10, 14, 15>(), createBitmaskToPress<2, 16, 18, 19, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 7>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 16, 18, 20, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 14>(), createBitmaskToPress<2, 16, 19, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 3, 6>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 13>(), createBitmaskToPress<2, 16, 18, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 8, 9, 12, 14, 15>(), createBitmaskToPress<2, 16, 19, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 8, 11, 12, 14, 15>(), createBitmaskToPress<2, 17, 18, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 3, 5, 7>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 3, 4, 6, 7>(), createBitmaskToPress<1, 12, 14, 15>(), createBitmaskToPress<2, 18, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 4, 5, 6, 7>(), createBitmaskToPress<1, 12, 13>(), createBitmaskToPress<2, 18, 19, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 3, 4, 6, 7>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 16, 18, 19, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 6>(), createBitmaskToPress<1, 8, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 4, 6>(), createBitmaskToPress<1, 8, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 2, 3, 4, 6>(), createBitmaskToPress<1, 9, 12>(), createBitmaskToPress<2, 16, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 7>(), createBitmaskToPress<1, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 9, 11, 13>(), createBitmaskToPress<2, 16, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 7>(), createBitmaskToPress<1, 8, 9, 10>(), createBitmaskToPress<2, 16, 19, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 9, 14>(), createBitmaskToPress<2, 16, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 7>(), createBitmaskToPress<1, 8, 10, 11, 15>(), createBitmaskToPress<2, 16, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 6, 7>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 16, 18, 20, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 2, 4, 6, 7>(), createBitmaskToPress<1, 8, 13, 14>(), createBitmaskToPress<2, 16, 18, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1, 2, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 13>(), createBitmaskToPress<2, 17, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 6>(), createBitmaskToPress<1, 8, 12, 13, 14, 15>(), createBitmaskToPress<2, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 16, 18, 19, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6, 7>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 3, 6>(), createBitmaskToPress<1, 8, 10, 12, 14>(), createBitmaskToPress<2, 17, 18, 20, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 5, 6>(), createBitmaskToPress<1, 9, 10, 12, 15>(), createBitmaskToPress<2, 16, 18, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 6>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 6, 7>(), createBitmaskToPress<1, 8, 12, 13, 14, 15>(), createBitmaskToPress<2, 18, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6, 7>(), createBitmaskToPress<1, 9, 10, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5, 7>(), createBitmaskToPress<1, 8, 9, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 8, 10, 11>(), createBitmaskToPress<2, 17, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 5, 6, 7>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 13>(), createBitmaskToPress<2, 16, 18, 20, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 7>(), createBitmaskToPress<1, 8, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 6>(), createBitmaskToPress<1, 8, 9, 12, 15>(), createBitmaskToPress<2, 16, 18, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5, 6>(), createBitmaskToPress<1, 8, 10, 11>(), createBitmaskToPress<2, 16, 17, 18, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 6, 7>(), createBitmaskToPress<1, 8, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 17, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 19, 20, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6, 7>(), createBitmaskToPress<1, 8, 12, 13, 14>(), createBitmaskToPress<2, 18, 19, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6>(), createBitmaskToPress<1, 8, 10, 12, 13>(), createBitmaskToPress<2, 16, 17, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 12, 15>(), createBitmaskToPress<2, 16, 18, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 6>(), createBitmaskToPress<1, 8, 12, 15>(), createBitmaskToPress<2, 17, 18, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 6>(), createBitmaskToPress<1, 8, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 19, 20, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 6>(), createBitmaskToPress<1, 10, 11, 12>(), createBitmaskToPress<2, 16, 17, 18, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 6>(), createBitmaskToPress<1, 9, 10, 12, 15>(), createBitmaskToPress<2, 16, 17, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3>(), createBitmaskToPress<1, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 6, 7>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 16, 18, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5, 6>(), createBitmaskToPress<1, 8, 10, 11, 12, 13, 15>(), createBitmaskToPress<2, 18, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 14, 15>(), createBitmaskToPress<2, 16, 17, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 6>(), createBitmaskToPress<1, 8, 9, 11, 14>(), createBitmaskToPress<2, 16, 18, 19, 20, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 6, 7>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 16, 18, 19, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 11, 13>(), createBitmaskToPress<2, 16, 18, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 11, 12, 13>(), createBitmaskToPress<2, 16, 17, 20, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 17, 18, 19, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 6, 7>(), createBitmaskToPress<1, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 5>(), createBitmaskToPress<1, 8, 9, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 11, 12, 14>(), createBitmaskToPress<2, 16, 18, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 6>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 17, 18, 19, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 3, 4, 6>(), createBitmaskToPress<1, 8, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2>(), createBitmaskToPress<1, 8, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 16, 18, 19, 21, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 7>(), createBitmaskToPress<1, 8, 9, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 13>(), createBitmaskToPress<2, 16, 18, 19, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 6>(), createBitmaskToPress<1, 8, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 13>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 2, 3, 5, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 10, 12>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 2, 4, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 14>(), createBitmaskToPress<2, 16, 18, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 14>(), createBitmaskToPress<2, 17, 18, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 6, 7>(), createBitmaskToPress<1, 8, 10, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 5, 6, 7>(), createBitmaskToPress<1, 10, 12, 14>(), createBitmaskToPress<2, 16, 18, 19, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 13, 14, 15>(), createBitmaskToPress<2, 16, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 5, 6>(), createBitmaskToPress<1, 8, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 5, 6, 7>(), createBitmaskToPress<1, 8, 11, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 20, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 6>(), createBitmaskToPress<1, 8, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 20, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 6>(), createBitmaskToPress<1, 8, 12, 15>(), createBitmaskToPress<2, 16, 17, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 6>(), createBitmaskToPress<1, 8, 12, 13, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 10, 12, 15>(), createBitmaskToPress<2, 16, 17, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 2, 6>(), createBitmaskToPress<1, 8, 11, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 2, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 8, 9, 10, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6>(), createBitmaskToPress<1, 8, 11, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 19, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 5, 6>(), createBitmaskToPress<1, 8, 10, 11, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 20, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6>(), createBitmaskToPress<1, 8, 10, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 19, 20, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 11, 12>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 6, 7>(), createBitmaskToPress<1, 8, 10, 11, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6>(), createBitmaskToPress<1, 8, 9, 10, 11, 12, 13>(), createBitmaskToPress<2, 16, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 5, 6>(), createBitmaskToPress<1, 8, 9, 12>(), createBitmaskToPress<2, 16, 18, 20, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 5, 6, 7>(), createBitmaskToPress<1, 8, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 10, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 6, 7>(), createBitmaskToPress<1, 8, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 6>(), createBitmaskToPress<1, 8, 9, 11, 12, 14>(), createBitmaskToPress<2, 16, 17, 18, 19>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 6>(), createBitmaskToPress<1, 8, 9, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6, 7>(), createBitmaskToPress<1, 8, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 4, 6>(), createBitmaskToPress<1, 8, 9, 12, 14>(), createBitmaskToPress<2, 16, 18, 19, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6>(), createBitmaskToPress<1, 8, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 19, 20, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 21, 22, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 4, 6>(), createBitmaskToPress<1, 8, 9, 12, 14, 15>(), createBitmaskToPress<2, 16, 17, 18, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5, 6>(), createBitmaskToPress<1, 8, 9, 12, 13, 14>(), createBitmaskToPress<2, 16, 17, 18, 21, 22>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 2, 6, 7>(), createBitmaskToPress<1, 8, 10, 11, 12>(), createBitmaskToPress<2, 16, 18, 19, 20, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 5, 6>(), createBitmaskToPress<1, 8, 11, 12, 15>(), createBitmaskToPress<2, 16, 17, 18, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 5, 6, 7>(), createBitmaskToPress<1, 8, 9, 12, 13, 15>(), createBitmaskToPress<2, 16, 18, 20, 21, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 4, 6>(), createBitmaskToPress<1, 8, 9, 12, 13, 14, 15>(), createBitmaskToPress<2, 16, 18, 21, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 6, 7>(), createBitmaskToPress<1, 8, 10, 11, 12, 15>(), createBitmaskToPress<2, 16, 18, 19, 21>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 4, 6, 7>(), createBitmaskToPress<1, 8, 10, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 4, 5, 6, 7>(), createBitmaskToPress<1, 8, 12, 13>(), createBitmaskToPress<2, 16, 18, 19, 21, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 5, 6, 7>(), createBitmaskToPress<1, 8, 9, 11, 12>(), createBitmaskToPress<2, 16, 18, 21, 23>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0, 1, 3, 4, 5, 6>(), createBitmaskToPress<1, 8, 11, 12, 13, 15>(), createBitmaskToPress<2, 16, 17, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 2, 3, 6>(), createBitmaskToPress<1, 8, 9, 10, 12>(), createBitmaskToPress<2, 16, 17, 18, 20, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1, 6, 7>(), createBitmaskToPress<1, 8, 9, 10, 12, 14, 15>(), createBitmaskToPress<2, 16, 18, 19, 23>(), createBitmaskToPress<3, 24>()},
};
typedef uint16_t LevelIndex;
LevelIndex constexpr numberOfLevels = sizeof(levels) / sizeof(levels[0]);


LevelIndex incrementedLevelIndex(LevelIndex const levelIndex)
{
    LevelIndex modLevelIndex = levelIndex + 1;

    if (numberOfLevels == modLevelIndex)
    {
        modLevelIndex = 0;
    }

    return modLevelIndex;
}

LevelIndex decrementedLevelIndex(LevelIndex const levelIndex)
{
    LevelIndex modLevelIndex = numberOfLevels - 1;
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

static void readLevelToDataIn(LevelIndex const levelIndex)
{
    static_assert(sizeof(dataIn) == sizeof(levels[0]));

    // Read level button presses to dataIn.
    for (size_t index = 0; index < 4; ++index)
    {
        dataIn[index] = pgm_read_byte_near(levels[levelIndex] + index);
    }
}

static void initializeDataOutToLevel(LevelIndex const levelIndex)
{
    readLevelToDataIn(levelIndex);
    // Clear the output.
    memset(dataOut, 0, sizeof(dataOut));
    // Now generate initial level by evaluating the "virtual" button presses.
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
    static void impl(LevelIndex const levelIndex)
    {
        // Show number of single-digit overruns in binary-coded number.
        LevelIndex const levelIndexSingleDigitOverrun = (levelIndex / 0x10);
        // Offset above number by 1, as to always have at least 1 LED lit up.
        if (0 != ((0b1 << Index) & (levelIndexSingleDigitOverrun + 1)))
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
    LevelIndex levelIndex;
    uint8_t dataOut[4];
    uint8_t buttonPresses;
    Mode mode;

    BackupValues(LevelIndex const levelIndex_,
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

// Interrupt Service Routine for when Timer2 matches OCR2A.
ISR (TIMER2_COMPA_vect)
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
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
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


bool levelSelectorLongPressDurationActive(uint8_t const levelSelectorLongPressDuration)
{
    // ramp up selection speed
    switch (levelSelectorLongPressDuration)
    {
    case 0:
        // fall through
    case 5:
        // fall through
    case 10:
        // fall through
    case 14:
        // fall through
    case 18:
        // fall through
    case 21:
        // fall through
    case 24:
        // fall through
    case 27:
        // fall through
    case 29:
        // fall through
    case 31:
        // fall through
    case 33:
        // fall through
    case 35:
    {
        return true;
    }
    default:
    {
        return (37 <= levelSelectorLongPressDuration);
    }
    }
}


int main()
{
    typedef ArduinoUno::pinC5 VccPeriphery;
    VccPeriphery::setType(AvrInputOutput::OutputLow);

    cli(); // disable interrupts

    // disable ADC conversions -> analogRead non-usable
    ADCSRA = 0b00010000; // ADC Control and Status Register A: ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0: ADC disable, ADIF cleared, ADC interrupts disabled
    // disable Analog Comparator -> everything regarding analog measurements non-usable
    ACSR = 0b10010000; // Analog Comparator Control and Statur Register: ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0: AC disabled, ACI cleared, AC interrupts disabled

    // this reconfigures TIMER2 - thus PWM [analogWrite] will not work as expected on Pins 3 and 11
    TCCR2A = 0b00000010; // COM2A1, COM2A0, COM2B1, COM2B0, 0, 0, WGM21, WGM20: no output, CTC-mode
    TCCR2B = 0b00000111; // FOC2A, FOC2B, 0, 0, WGM22, CS22, CS21, CS20: 1024 prescaler
    OCR2A = 196; // Output compare register [196 * 1024 @ 2MHz = 100352us]
    TIMSK2 = 0b00000010; // 0, 0, 0, 0, 0, OCIE2B, OCIE2A, TOIE2: Output Compare Match Interrupt Enable Timer2 A


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
    LevelIndex levelIndex = 0;
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
            while (ButtonOnOff::isUp())
            {
                powerOff();
                ButtonOnOff::update();
            }
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
            static uint8_t levelSelectorLongPressDuration = 0;
            if (ButtonUp::isDown() && ButtonDown::isDown())
            {
                // Do nothing if both up and down are pressed.
                levelSelectorLongPressDuration = 0;
            }
            else if (ButtonUp::isDownLong())
            {
                levelSelectorLongPressDuration = incrementUint8Capped(levelSelectorLongPressDuration);
                if (levelSelectorLongPressDurationActive(levelSelectorLongPressDuration))
                {
                    levelIndex = incrementedLevelIndex(levelIndex);
                }
            }
            else if (ButtonDown::isDownLong())
            {
                levelSelectorLongPressDuration = incrementUint8Capped(levelSelectorLongPressDuration);
                if (levelSelectorLongPressDurationActive(levelSelectorLongPressDuration))
                {
                    levelIndex = decrementedLevelIndex(levelIndex);
                }
            }
            else
            {
                levelSelectorLongPressDuration = 0;

                if (ButtonUp::releasedAfterShort())
                {
                    levelIndex = incrementedLevelIndex(levelIndex);
                }
                if (ButtonDown::releasedAfterShort())
                {
                    levelIndex = decrementedLevelIndex(levelIndex);
                }
            }

            if (ButtonEnter::releasedAfterShort())
            {
                mode = Mode::Game;
                initializeDataOutToLevel(levelIndex);
                buttonPresses = 0;
                levelSelectorLongPressDuration = 0;
            }
            else if (ButtonEscapeReset::releasedAfterShort())
            {
                memcpy(dataOut, backupValues.dataOut, 4);
                levelIndex = backupValues.levelIndex;
                buttonPresses = backupValues.buttonPresses;
                mode = Mode::Game;
                levelSelectorLongPressDuration = 0;
            }
            else
            {
                // Update level selection display.
                readSingleDigitToDataOut(levelIndex);
                Loop<4, WrapperLedLevelsUpdate, LevelIndex>::impl(levelIndex);
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
                readLevelToDataIn(levelIndex); // misuse dataIn - it will be overwritten on next read-in from HW
                uint8_t pressedButtonsCountForLevel = 0;
                Loop<24, WrapperCountButtonsPressed_, uint8_t &>::impl(pressedButtonsCountForLevel);

                uint8_t const buttonPressesDelta = buttonPresses - pressedButtonsCountForLevel;
                // Update level selection display.
                readSingleDigitToDataOut(buttonPressesDelta);
                Loop<4, WrapperLedLevelsUpdate, LevelIndex>::impl(buttonPressesDelta);

                Leds<14>::set(SimpleOnOffProperties::State::On);
            }
            break;
        }
        }

        displayDataOut();

        // Wait some time as to not pull/push the shift-registers too often.
        // Use TIMER2_COMPA_vect for wakeup and wait in SLEEP_MODE_PWR_SAVE.
        sei();
        powerDown();
    }
}
