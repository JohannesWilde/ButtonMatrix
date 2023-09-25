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

struct MatrixAccess
{
    uint8_t byteIndex;
    uint8_t bitMask;
};

template <uint8_t matrixWidth, uint8_t matrixHeight>
MatrixAccess matrixAccess(uint8_t const index)
{
    uint8_t const byteIndex = index / 8;
    uint8_t const bitOffset = index - 8 * byteIndex;
    uint8_t const bitMask = (0b1 << bitOffset);
    return MatrixAccess{byteIndex, bitMask};
}

int main()
{
    typedef ArduinoUno arduinoUno;

    typedef arduinoUno::pinC5 VccPeriphery;
    VccPeriphery::setType(AvrInputOutput::OutputLow);

    typedef RsLatch<DummyAvrPin1, arduinoUno::pinC1, DummyAvrPin1> buttonsInLatcher;
    buttonsInLatcher::initialize();

    uint8_t constexpr shiftRegisterBitsCount = 32;
    uint8_t constexpr matrixWidthAndHeight = 5;
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

    uint8_t dataIn[4] = {0x00, 0x00, 0x00, 0x00};
    uint8_t dataOut[4] = {0x00, 0x00, 0x00, 0x00};

    while (true)
    {
        // Latch bits in shift-register for read-out from the buttons.
        buttonsInShiftRegister::loadParallelToShiftregister();
        // Reset latches in front of read-out-shiftregisters.
        buttonsInLatcher::reset();
        // Actually copy the latched shift-register values to data.
        buttonsInShiftRegister::shiftOutBits(dataIn);

        for (uint8_t index = 0; index < (matrixWidthAndHeight * matrixWidthAndHeight); ++index)
        {
            MatrixAccess matrixAccessIn = matrixAccess<matrixWidthAndHeight, matrixWidthAndHeight>(index);

            if (0 != (dataIn[matrixAccessIn.byteIndex] & matrixAccessIn.bitMask))
            {
                {
                    dataOut[matrixAccessIn.byteIndex] ^= matrixAccessIn.bitMask;
                }
                if (0 != (index % matrixWidthAndHeight))
                {
                    uint8_t const indexNeighbor = index - 1;
                    MatrixAccess matrixAccessNeighbor = matrixAccess<matrixWidthAndHeight, matrixWidthAndHeight>(indexNeighbor);
                    dataOut[matrixAccessNeighbor.byteIndex] ^= matrixAccessNeighbor.bitMask;
                }
                if ((matrixWidthAndHeight - 1) != (index % matrixWidthAndHeight))
                {
                    uint8_t const indexNeighbor = index + 1;
                    MatrixAccess matrixAccessNeighbor = matrixAccess<matrixWidthAndHeight, matrixWidthAndHeight>(indexNeighbor);
                    dataOut[matrixAccessNeighbor.byteIndex] ^= matrixAccessNeighbor.bitMask;
                }
                if (matrixWidthAndHeight <= index)
                {
                    uint8_t const indexNeighbor = index - matrixWidthAndHeight;
                    MatrixAccess matrixAccessNeighbor = matrixAccess<matrixWidthAndHeight, matrixWidthAndHeight>(indexNeighbor);
                    dataOut[matrixAccessNeighbor.byteIndex] ^= matrixAccessNeighbor.bitMask;
                }
                if ((matrixWidthAndHeight * (matrixWidthAndHeight - 1)) > index)
                {
                    uint8_t const indexNeighbor = index + matrixWidthAndHeight;
                    MatrixAccess matrixAccessNeighbor = matrixAccess<matrixWidthAndHeight, matrixWidthAndHeight>(indexNeighbor);
                    dataOut[matrixAccessNeighbor.byteIndex] ^= matrixAccessNeighbor.bitMask;
                }
            }
        }

        // Move data to the LED shiftRegister.
        ledsOutShiftRegister::shiftInBits(dataOut);
        // Apply the shifted-in bits to the output of the shift-registers.
        ledsOutShiftRegister::showShiftRegister();

        // Wait some time as to not pull/push the shift-registers too often.
        _delay_ms(300);
    }
}
