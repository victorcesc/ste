all:
	avr-g++ -mmcu=atmega328p timer_test.cpp gpio_pin.cpp uart.cpp adc.cpp timer.cpp -o main
	avr-objcopy -O ihex main main.ihex
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -U flash:w:main.ihex