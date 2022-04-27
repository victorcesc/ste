all:
	avr-gcc -mmcu=atmega328p main.cpp gpio_pin.cpp -o main
	avr-objcopy -O ihex main main.ihex
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -U flash:w:main.ihex