// this is only for the QtCreator to find the correct highlighting - this is already defined somewhere before
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ArduinoDrivers/arduinouno.hpp"

//#include "ArduinoDrivers/rslatchcd4043b.hpp"
//#include "ArduinoDrivers/shiftregister74hc595.hpp"
//#include "ArduinoDrivers/parallelinshiftregister74hc165.hpp"

int main()
{
    typedef ArduinoUno arduinoUno;

    arduinoUno::LED_BUILTIN::setType(AvrInputOutput::OUTPUT_HIGH);
    while (true)
    {
        _delay_ms(1000);
        arduinoUno::LED_BUILTIN::clearPort();
        _delay_ms(1000);
        arduinoUno::LED_BUILTIN::setPort();
    }
}
