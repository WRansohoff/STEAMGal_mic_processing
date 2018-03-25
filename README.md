# Overview

This is some firmware for the 'STEAMGal' credit card-sized educational development platform I've been working on. I've found that the same boards work fairly interchangeably with both STM32F051 and STM32F303 chips. The F303s have hardware instructions for floating-point calculations and DSP functions, and I think their CMSIS libraries have FFT functions. So, why not try making a program to listen to music?

It will listen for analog values from an electret microphone - probably amplified somehow - and convert from the time domain to the frequency domain every N samples. The result probably just be drawn on the screen initially, but I see it being used for driving LED displays or something, if it winds up working at all.

The files under 'lib/' are probably not necessary, I just keep having GCC get confused about which 'libc's to use with armv6m for some reason.

# Current Status

Currently, the only functionality is reading an analog channel on pin A1 to a variable every loop; sampling is not done on a consistent schedule, nor is it processed by an FFT, nor is the value displayed anywhere.

So, basically nothing.

# Connections

The 128x64 monochrome SSD1306 OLED display uses the I2C1 bus on pins B6 and B7. A 4-pin header near the top of the board makes the I2C1 peripheral available for other devices which use that protocol for communication. For now, the display's I2C address is 0x78 and cannot be changed, but I might add a jumper for changing it to 0x7A in future revisions of the board.

There is a piezo buzzer on pin B0.

There is an LED on pin A12.

The 6 buttons are on pins A2-A7. (And a 'reset' button connected to the NRST pin):

* A2: Left
* A3: Up
* A4: Down
* A5: Right
* A6: 'B' button.
* A7: 'A' button.

I forgot to add an EEPROM module on the first revision of the board. Oops. Future revisions will probably have a 24LC16BT chip on the I2C1 bus, which will occupy addresses 0b1010xyzR, where 'x', 'y', and 'z' are used to select which of eight 2KB blocks to address.

Pins A0, A1, and B1 are available on a 'GPIO1' 5-pin 0.1" header. +3V3 and GND occupy the other two pins. This project uses pin A1 to read an external breadboard-ed microphone circuit or breakout board.

Pins B3, B4, B5, and A15 are available on a 'GPIO2' 6-pin 0.1" header. +3V3 and GND occupy the other two pins. Pins B3-B5 are connected to the SPI1 peripheral on QFP32 STM32 chips, and some SPI protocols have a separate 'Data/Command' line.

Pins A8 and A9 are available on a 4-pin 0.2mm JST connector, with +3V3 and GND occupying the other two pins.

Pins A10 and A11 are also available on a 4-pin 0.2mm JST connector, with +3V3 and GND occupying the other two pins.

Pins A13 and A14 are connected to a 4-pin programming header with GND and input voltage (~3.5 - 13.2V). They aren't intended to be re-assigned, as the board is intended to be easy to reprogram.

# Core processor

This application will likely depend on the DSP functionality in the F303K8 chip, as it has hardware instructions for floating-point calculations and DSP functions. But I will try to maintain a functional version for the F051K8 as well; it would be nice to compare performance, anyways.
