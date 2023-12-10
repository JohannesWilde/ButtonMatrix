add_subdirectory(ArduinoDrivers)
add_subdirectory(helpers)

#####################################################################
# simple AVR executable
#####################################################################
add_avr_executable(main
   main.cpp
   )

#####################################################################
# libraries to link to
#####################################################################
target_link_libraries(main${MCU_TYPE_FOR_FILENAME}.elf
    PRIVATE arduinoDrivers
    PRIVATE helpers
    )
