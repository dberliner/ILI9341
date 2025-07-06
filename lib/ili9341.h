/** 
 * ---------------------------------------------------------------+ 
 * @desc        ILI9341 LCD Driver 
 * ---------------------------------------------------------------+ 
 *              Copyright (C) 2020 Marian Hrinko.
 *              Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @datum       10.12.2020
 * @file        ili9341.h
 * @update      13.12.2020
 * @version     1.0
 * @tested      AVR Atmega328p
 *
 * @depend      font
 *
 */

#ifndef __ILI9341_H__
#define __ILI9341_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

  // HW INTERFACE
  // ---------------------------------------------------------------
  /* These enums are named verbosely becuase different boards will have different active levels and the required behavior isn't obvious */
  typedef enum {
    RESET_HIGH_NOTSET,
    RESET_LOW_SET
  } ili9341_reset_e;

  typedef enum {
    DC_LOW_CMD,
    DC_HIGH_DATA
  } ili9341_dc_e;

  typedef enum {
    CS_LOW_ON,
    CS_HIGH_OFF
  } ili9341_cs_e;

  typedef struct {
    uint16_t len;
    uint8_t *buf;
  } ili9341_buf_t;

  typedef struct {
    void (*reset_pin)(ili9341_reset_e);
    void (*dc_pin)(ili9341_dc_e);
    void (*cs_pin)(ili9341_cs_e);
    void (*delay)(uint32_t);

    /**
     * \brief Sends a buffer to the device
     *
     * This function sends the contents of the passed buffer. No internal buffering is performed and the entire buffer is send.
     * This is intended for use in DMA transmissions where a sequence of pixels needs to be sent repeatedly, maximizing DMA transfers
     * in favor of continually writing to system memory.
     *
     * The address at buf->buf should be assumed as "in use" (IE by a DMA transfer) until barrier is called.
     *
     * \param buf A pointer to an ili9341_buf struct
     */
    void (*sendbuf)(const ili9341_buf_t*);

    /**
     * \brief Sends a byte to the device
     *
     * This function sends a byte to the device. Implementations are allowed to buffer the data to send it in bulk. Call commit to ensure that all bytes have
     * actually been sent.
     *
     * \param unused Unued, pass NULL.
     */
    void (*sendbyte)(uint8_t);

    /**
     * \brief Finishes a transaction
     *
     * This function must be called after sendbyte references to ensure that all data is sent to the device
     *
     * \param unused Unused, pass NULL.
     */
    void (*commit)(void *_unused);

    /**
     * \brief Blocks until any current TX operations are done
     *
     * This function blocks during concurrent (IE DMA) transactions so control lines are not changed mid-transactions.
     * If SPI the send calls are blocking this function does not need to be implemented.
     *
     * \param unused Unused, pass NULL.
     */
    void (*barrier)(void *_unused);
  } ili9341_hw_intf_t;

  void ili9341_set_hw_intf(const ili9341_hw_intf_t *hw_intf);


  // COMMAND DEFINITION
  // ---------------------------------------------------------------
  #define ILI9341_NOP           0x00  // No Operation
  #define ILI9341_SWRESET       0x01  // Software Reset
  #define ILI9341_RDDIDIF       0x04  // Read Display Identification Information
  #define ILI9341_RDDST         0x09  // Read Display Status
  #define ILI9341_RDDPM         0x0A  // Read Display Power Mode
  #define ILI9341_RDDMADCTL     0x0B  // Read Display MADCTL
  #define ILI9341_RDDCOLMOD     0x0C  // Read Display Pixel Format
  #define ILI9341_RDDIM         0x0D  // Read Display Image Format
  #define ILI9341_RDDSM         0x0E  // Read Display Signal Mode
  #define ILI9341_RDDSDR        0x0F  // Read Display Self Diagnostics Result
  // ---------------------------------------------------------------
  #define ILI9341_SLPIN         0x10  // Enter Sleep Mode
  #define ILI9341_SLPOUT        0x11  // Sleep Out
  #define ILI9341_PTLON         0x12  // Partial Mode On
  #define ILI9341_NORON         0x13  // Normal Display On
  // ---------------------------------------------------------------
  #define ILI9341_DINVOFF       0x20  // Dislpay Inversion Off
  #define ILI9341_DINVON        0x21  // Dislpay Inversion On
  #define ILI9341_GAMSET        0x26  // Gamma Set  
  #define ILI9341_DISPOFF       0x28  // Display OFF
  #define ILI9341_DISPON        0x29  // Display ON
  #define ILI9341_CASET         0x2A  // Column Address Set
  #define ILI9341_PASET         0x2B  // Page Address Set
  #define ILI9341_RAMWR         0x2C  // Memory Write
  #define ILI9341_RGBSET        0x2D  // Color Set
  #define ILI9341_RAMRD         0x2E  // Memory Read
  // ---------------------------------------------------------------
  #define ILI9341_PLTAR         0x30  // Partial Area
  #define ILI9341_VSCRDEF       0x33  // Vertical Scroll Definition
  #define ILI9341_TEOFF         0x34  // Tearing Effect Line OFF
  #define ILI9341_TEON          0x35  // Tearing Effect Line ON
  #define ILI9341_MADCTL        0x36  // Memory Access Control
  #define ILI9341_VSSAD         0x37  // Vertical Scrolling Start Address
  #define ILI9341_IDMOFF        0x38  // Idle Mode OFF
  #define ILI9341_IDMON         0x39  // Idle Mode ON
  #define ILI9341_COLMOD        0x3A  // Pixel Format Set
  #define ILI9341_WMCON         0x3C  // Write Memory Continue
  #define ILI9341_RMCON         0x3E  // Read Memory Continue
  // ---------------------------------------------------------------
  #define ILI9341_IFMODE        0xB0  // RGB Interface Signal Control
  #define ILI9341_FRMCRN1       0xB1  // Frame Control (In Normal Mode)
  #define ILI9341_FRMCRN2       0xB2  // Frame Control (In Idle Mode)
  #define ILI9341_FRMCRN3       0xB3  // Frame Control (In Partial Mode)
  #define ILI9341_INVTR         0xB4  // Display Inversion Control
  #define ILI9341_PRCTR         0xB5  // Blanking Porch Control
  #define ILI9341_DISCTRL       0xB6  // Display Function Control
  #define ILI9341_ETMOD         0xB7  // Entry Mode Set
  #define ILI9341_BKCR1         0xB8  // Backlight Control 1
  #define ILI9341_BKCR2         0xB9  // Backlight Control 2
  #define ILI9341_BKCR3         0xBA  // Backlight Control 3
  #define ILI9341_BKCR4         0xBB  // Backlight Control 4
  #define ILI9341_BKCR5         0xBC  // Backlight Control 5
  #define ILI9341_BKCR7         0xBE  // Backlight Control 7
  #define ILI9341_BKCR8         0xBF  // Backlight Control 8
  // ---------------------------------------------------------------
  #define ILI9341_PWCTRL1       0xC0  // Power Control 1
  #define ILI9341_PWCTRL2       0xC1  // Power Control 2
  #define ILI9341_VCCR1         0xC5  // VCOM Control 1
  #define ILI9341_VCCR2         0xC7  // VCOM Control 2
   // ---------------------------------------------------------------
  #define ILI9341_RDID1         0xDA  // Read ID1
  #define ILI9341_RDID2         0xDB  // Read ID2
  #define ILI9341_RDID3         0xDC  // Read ID3
  // ---------------------------------------------------------------
  #define ILI9341_GMCTRP1       0xE0  // Positive Gamma Correction
  #define ILI9341_GMCTRN1       0xE1  // Neagtove Gamma Correction

  // Extend register commands
  // --------------------------------------------------------------- 
  // @source https://github.com/fagcinsk/stm-ILI9341-spi/blob/master/lib/ILI9341/commands.h
  //
  #define ILI9341_LCD_POWERA    0xCB   // Power control A register
  #define ILI9341_LCD_POWERB    0xCF   // Power control B register
  #define ILI9341_LCD_DTCA      0xE8   // Driver timing control A
  #define ILI9341_LCD_DTCB      0xEA   // Driver timing control B
  #define ILI9341_LCD_POWER_SEQ 0xED   // Power on sequence register
  #define ILI9341_LCD_3GAMMA_EN 0xF2   // 3 Gamma enable register
  #define ILI9341_LCD_PRC       0xF7   // Pump ratio control register


  // SOFTWARE DEFINITION
  // ---------------------------------------------------------------
  #define ILI9341_SUCCESS       0
  #define ILI9341_ERROR         1

  // Colors
  #define ILI9341_BLACK         0x0000
  #define ILI9341_WHITE         0xFFFF
  #define ILI9341_RED           0xF000
  
  //R[0-31] G[0-63] B[0-31]
  #define ILI9341_RGB565(R,G,B) ((B & 0x1F) | ((G & 0x3F)<<5) | ((R & 0x1F)<<11))
  #define RGBR(RGB) ((RGB>>11)&0x1F)
  #define RGBG(RGB) ((RGB>>5)&0x3F)
  #define RGBB(RGB) (RGB&0x1F)
  #define ILI9341_RGB565_DECODE(RGB, R, G, B) R=RGBR(RGB); G=RGBG(RGB); B=RGBB(RGB);
  #define ILI9341_RGB565_DECODETOBUF(OUTBUF, RGB)          \
          ((uint8_t*)OUTBUF)[0] = RGBR(RGB)<<3;            \
          ((uint8_t*)OUTBUF)[0] |= (RGBG(RGB)>>3) & 0x7;   \
          ((uint8_t*)OUTBUF)[1] = (RGBG(RGB)& 0x7)<<5;     \
          ((uint8_t*)OUTBUF)[1] |= RGBB(RGB) & 0x1F;

  //R[0-63] G[0-63] B[0-63]
  #define ILI9341_RGB666(R,G,B) (B & 0x3F) | (G & 0x3F)<<6 | (R & 0x3F)<<12

  // max columns
  #define ILI9341_MAX_X         240
  // max rows
  #define ILI9341_MAX_Y         320UL
  // columns max counter
  #define ILI9341_SIZE_X        ILI9341_MAX_X - 1
  // rows max counter
  #define ILI9341_SIZE_Y        ILI9341_MAX_Y - 1
  // whole pixels
  #define ILI9341_CACHE_MEM     (ILI9341_MAX_X * ILI9341_MAX_Y)

  /** @enum Font sizes */
  typedef enum {
    // 1x high & 1x wide size
    X1 = 0x00,
    // 2x high & 1x wide size
    X2 = 0x80,
    // 2x high & 2x wider size
    // 0x0A is set because need to offset 5 position to right
    //      when draw the characters of string 
    X3 = 0x81
  } ILI9341_Sizes;

  /** @const Command list ILI9341B */
  extern const uint8_t INIT_ILI9341[];

  /**
   * @desc    LCD Init
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_Init (void);

  /**
   * @desc    LCD Hardware Reset
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_HWReset (void);

 /**
   * @desc    LCD Init PORTs
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_InitPorts (void);

  /**
   * @desc    LCD Transmit Command
   *
   * @param   uint8_t
   *
   * @return  void
   */
  void ILI9341_TransmitCmmd (uint8_t);

  /**
   * @desc    LCD Transmit 8 bits data
   *
   * @param   uint8_t
   *
   * @return  void
   */
  void ILI9341_Transmit8bitData (uint8_t);

  /**
   * @desc    LCD Transmit 16 bits data
   *
   * @param   uint16_t
   *
   * @return  void
   */
  void ILI9341_Transmit16bitData (uint16_t);

  /**
   * @desc    LCD Transmit 32 bits data
   *
   * @param   uint32_t
   *
   * @return  void
   */
  void ILI9341_Transmit32bitData (uint32_t);

  /**
   * @desc    LCD Set window
   *
   * @param   uint16_t
   * @param   uint16_t
   * @param   uint16_t
   * @param   uint16_t 
   *
   * @return  char
   */
  char ILI9341_SetWindow (uint16_t, uint16_t, uint16_t, uint16_t);

  /**
   * @desc    LCD Write Color Pixels
   *
   * @param   uint16_t
   * @param   uint32_t
   *
   * @return  void
   */
  void ILI9341_SendColor565 (uint16_t, uint32_t);

  /**
   * @desc    LCD Draw Rectangle
   *
   * @param   uint16_t x Left top starting pos
   * @param   uint16_t y Left top starting pos
   * @param   uint16_t Width in px
   * @param   uint16_t Height in px
   * @param   uint16_t color in 565 format
   *
   * @return  char status
   */
  char ILI9341_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

  /**
   * @desc    LCD Draw Pixel
   *
   * @param   uint16_t
   * @param   uint16_t
   * @param   uint16_t
   *
   * @return  char
   */
  char ILI9341_DrawPixel (uint16_t, uint16_t, uint16_t);

  /**
   * @desc    LCD Clear screen
   *
   * @param   uint16_t
   *
   * @return  void
   */
  void ILI9341_ClearScreen (uint32_t);

  /**
   * @desc    LCD Inverse Screen
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_InverseScreen (void);

  /**
   * @desc    LCD Normal Screen
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_NormalScreen (void);

  /**
   * @desc    LCD Update Screen
   *
   * @param   void
   *
   * @return  void
   */
  void ILI9341_UpdateScreen (void);

  /**
   * @desc    LCD Draw line by Bresenham algoritm - depend on MADCTL
   *  
   * @param   uint16_t - x start position / 0 <= cols <= ILI9341_SIZE_X
   * @param   uint16_t - x end position   / 0 <= cols <= ILI9341_SIZE_X
   * @param   uint16_t - y start position / 0 <= rows <= ILI9341_SIZE_Y 
   * @param   uint16_t - y end position   / 0 <= rows <= ILI9341_SIZE_Y
   * @param   uint16_t - color
   *
   * @return  void
   */
  void ILI9341_DrawLine(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);

  /**
   * @desc    LCD Fast draw line horizontal - depend on MADCTL
   *
   * @param   uint16_t - x start position
   * @param   uint16_t - x end position
   * @param   uint16_t - y position
   * @param   uint16_t - color
   *
   * @return  char
   */
  char ILI9341_DrawLineHorizontal (uint16_t, uint16_t, uint16_t, uint16_t);

  /**
   * @desc    LCD Fast draw line vertical - depend on MADCTL
   *
   * @param   uint16_t - x position
   * @param   uint16_t - y start position
   * @param   uint16_t - y end position
   * @param   uint16_t - color
   *
   * @return  char
   */
  char ILI9341_DrawLineVertical (uint16_t, uint16_t, uint16_t, uint16_t);

  /**
   * @desc    LCD Draw character 2x larger
   *
   * @param   char -> character
   * @param   uint16_t -> color
   * @param   ILI9341_Sizes -> size
   *
   * @return  void
   */
  char ILI9341_DrawChar (char, uint16_t, ILI9341_Sizes);

  /**
   * @desc    LCD Check text position x, y
   *
   * @param   uint16_t x
   * @param   uint16_t y
   * @param   uint16_t max_y
   * @param   ILI9341_Sizes
   *
   * @return  char
   */
  char ILI9341_CheckPosition(uint16_t, uint16_t, uint16_t, ILI9341_Sizes);

  /**
   * @desc    LCD Set text position x, y
   *
   * @param   uint16_t x - position
   * @param   uint16_t y - position
   *
   * @return  char
   */
  char ILI9341_SetPosition(uint16_t, uint16_t);

    /**
   * @desc    Draws a string with background.
   *
   *          Drawing the text as a full block is far faster due to the lack of
   *          D/C switches and small transfers required.
   *
   * @param   char* -> string
   * @param   uint16_t -> color
   * @param   ILI9341_Sizes -> size
   *
   * @return  void
   */
  void ILI9341_DrawStringFast (char *str, uint16_t text_color, uint8_t size, uint16_t bg_color);

  /**
   * @desc    Draw string
   *
   * @param   char* -> string 
   * @param   uint16_t -> color
   * @param   ILI9341_Sizes -> size
   *
   * @return  void
   */
  void ILI9341_DrawString (char*, uint16_t, ILI9341_Sizes);

  /**
   * @desc    Delay
   *
   * @param   uint16_t
   *
   * @return  void
   */
  void ILI9341_Delay (uint16_t);

  /**
   * @desc    Renders a bitmap into pixel data in a memory buffer, scaling if the src and dst sizes are different
   *
   * @param   uint8_t* dst The buffer to write into. Must be at least dst_w*dst_h*2 bytes long because each pixel is two bytes
   * @param   uint16_t dst_w The width of the destination rectangle
   * @param   uint16_t dst_h The height of the destination rectangle
   * @param   uint8_t src The buffer of the bitmap being read from
   * @param   uint16_t src_w The width of the source rectangle
   * @param   uint16_t src_h The height of the source rectangle
   * @param   fg The foreground color (drawn if the corresponding bit is set)
   * @param   bg The background color (drawn if the corresponding bit is not set)
   *
   * @return  void
   */
  void ILI9341_RenderScaledBitmap(uint8_t* dst, uint16_t dst_w, uint16_t dst_h, const uint8_t* src, uint16_t src_w, uint16_t src_h, uint16_t fg565, uint16_t bg565);

  /**
   * @desc    Renders a bitmap into pixel data in a memory buffer, scaling if the src and dst sizes are different.
   *          This function is identical to ILI9341_RenderScaledBitmap except that the bitmap stores data in column-major order
   *
   * @param   uint8_t* dst The buffer to write into. Must be at least dst_w*dst_h*2 bytes long because each pixel is two bytes
   * @param   uint16_t dst_w The width of the destination rectangle
   * @param   uint16_t dst_h The height of the destination rectangle
   * @param   uint8_t src The buffer of the bitmap being read from
   * @param   uint16_t src_w The width of the source rectangle
   * @param   uint16_t src_h The height of the source rectangle
   * @param   fg The foreground color (drawn if the corresponding bit is set)
   * @param   bg The background color (drawn if the corresponding bit is not set)
   *
   * @return  void
   */
  void ILI9341_RenderScaledBitmapColMajor(uint8_t* dst, uint16_t dst_w, uint16_t dst_h, const uint8_t* src, uint16_t src_w, uint16_t src_h, uint16_t fg565, uint16_t bg565);

  /**
   * @desc    Renders a bitmap into pixel data in a memory buffer without scaling.
   *
   * @param   uint8_t* render_out The buffer to write into. Must be at least w*h*2 bytes long because each pixel is two bytes
   * @param   uint8_t* bitmap The buffer of the bitmap being read from
   * @param   uint16_t w The width of the destination rectangle
   * @param   uint16_t h The height of the destination rectangle
   * @param   fg The foreground color (drawn if the corresponding bit is set)
   * @param   bg The background color (drawn if the corresponding bit is not set)
   *
   * @return  void
   */
  void ILI9341_RenderBitmap(uint8_t* render_out, const uint8_t* bitmap, uint16_t w, uint16_t h, uint16_t fg565, uint16_t bg565);

  /**
   * @desc    Renders a bitmap into pixel data in a memory buffer without scaling.
   *          This function is identical to ILI9341_RenderBitmap except that the bitmap stores data in column-major order
   *
   * @param   uint8_t* render_out The buffer to write into. Must be at least w*h*2 bytes long because each pixel is two bytes
   * @param   uint8_t* bitmap The buffer of the bitmap being read from
   * @param   uint16_t w The width of the destination rectangle
   * @param   uint16_t h The height of the destination rectangle
   * @param   fg The foreground color (drawn if the corresponding bit is set)
   * @param   bg The background color (drawn if the corresponding bit is not set)
   *
   * @return  void
   */
  void ILI9341_RenderBitmapColMajor(uint8_t* render_out, const uint8_t* bitmap, uint16_t w, uint16_t h, uint16_t fg565, uint16_t bg565);

  /**
   * @desc    Writes a pattern of caller managed memory to a rectangular section of the screen
   *          This processs is much faster than sending individual pixels or requiring library
   *          controlled memory caching, but at the expense of requiring the caller to handle
   *          their own memory.
   *
   * @param   uint8_t* pattern_buf The buffer to continously write to the video memory
   * @param   uint16_t len The length to copy from pattern_buf
   * @param   x The starting X coordinate
   * @param   y The starting Y coordinate
   * @param   w The width of the draw in pixels (1 corresponds to a single pixel)
   * @param   h The height of the darw in pixels (1 corresponds to a single pixel)
   *
   * @return  void
   */
  void ILI9341_WritePatternRect(uint8_t *pattern_buf, uint16_t len, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

#endif
