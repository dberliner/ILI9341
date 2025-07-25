# C Library for ILI9341 2.8 TFT LCD Display

Based on https://github.com/Matiasus/ILI9341 this library removes all vendor-level dependencies and gives the caller the ability to hook
their HAL into the operations.

## ILI9341 Description
Detailed information are described in [Datasheet ILI9341](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf).

## Library
C library is aimed for driving [ILI9341 2.8 TFT LCD display](#demonstration) 240x320

## Hardware connection
This library is platform independent and uses optional hooks. All hook are simply not called if NULL
- reset_pin, dc_pin, cs_pin | Set the respective pins
- delay | Delay microseconds
- sendbyte | Writes a single byte of data. The implementation does not have to immediately send the data and may buffer it for sending in bulk.
- commit | Send all remaining data in the buffer


### Usage
TODO: Explain the driver here

## Links
- [Datasheet ILI9341](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)

### Tested
Library was tested on a **_HiLetgo ILI9341 2.8" SP TFT Dispay_** with **_STM32F072B-DISCO_**. See [ILI9341-STM32F072B](https://github.com/dberliner/ILI9341-STM32F072B) for the demonstrations implementation.

## Demonstration
<img src="img/img.jpg" />

## Acknowledgement
- [Adafuit TFT](https://github.com/adafruit/TFTLCD-Library)
- [notro](https://github.com/notro/fbtft/blob/master/fb_ili9341.c)
- [thefallenidealist](https://github.com/thefallenidealist/ili9341/blob/master/glcd.c)
- [fagcinsk](https://github.com/fagcinsk/stm-ILI9341-spi/blob/master/lib/ILI9341/commands.h)
- [Matiasus](https://github.com/Matiasus/ILI9341)