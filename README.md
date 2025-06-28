# C Library for ILI9341 2.8 TFT LCD Display

Based on https://github.com/Matiasus/ILI9341 this library removes all vendor-level dependencies and gives the caller the ability to hook
their HAL into the operations.

## ILI9341 Description
Detailed information are described in [Datasheet ILI9341](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf).

## Library
C library is aimed for driving [ILI9341 2.8 TFT LCD display](#demonstration) 240x320 using 8080-I Series Parallel Interface.

## Hardware connection
This library is platform independent and uses optional hooks. All hook are simply not called if NULL
- reset_pin, dc_pin, cs_pin | Set the respective pins
- delay | Delay microseconds
- sendbyte | Writes a single byte of data
- commit | Ran after an entire command is sent via sentbyte. Optional if sendbyte actually sends over the wire and is blocking

TODO: Make driver model make sense for async transfers eg. DMA

### Usage
See [INSERT PARENT REPO HERE] for an example using this library on a STM32F072b discovery board

## Links
- [Datasheet ILI9341](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)

## Acknowledgement
- [Adafuit TFT](https://github.com/adafruit/TFTLCD-Library)
- [notro](https://github.com/notro/fbtft/blob/master/fb_ili9341.c)
- [thefallenidealist](https://github.com/thefallenidealist/ili9341/blob/master/glcd.c)
- [fagcinsk](https://github.com/fagcinsk/stm-ILI9341-spi/blob/master/lib/ILI9341/commands.h)
- [Matiasus](https://github.com/Matiasus/ILI9341)