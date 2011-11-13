/**
 * SDCC - PIC libraries
 * 
 * lcd_string.h
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __SDCC_LCD_STRING_LIBRARY_H__
#define __SDCC_LCD_STRING_LIBRARY_H__ 1

#ifndef __SDCC_LCD_DRIVER_H__
    #error The lcd driver must be included.
#endif

/**
 * void lcd_put_char(unsigned char c)
 * 
 * Puts a char at pre-specified position
 * 
 * @param   unsigned char c     The char to be writed
 * @return  void
 */
void lcd_put_char(unsigned char c);

/**
 * uint8_t lcd_put_string(unsigned char *buffer, uint8_t count)
 * 
 * Retrieves a char from the lcd device at pre-specified position
 * 
 * @param   unsigned char x     The x position in the lcd
 * @param   unsigned char y     The y position in the lcd
 * @return  unsigned char       The read char
 */
unsigned char lcd_get_char(unsigned char x, unsigned char y);

/**
 * void lcd_put_string(char *buffer, uint8_t count)
 * 
 * Puts a string on the device screen
 * 
 * @param   unsigned char *buffer   The char buffer
 * @param   uint8_t count           How many chars will put
 * @return  uint8_t                 How many chars was placed
 */
uint8_t lcd_put_string(unsigned char *buffer, uint8_t count);

/**
 * void lcd_put_string_at(char *buffer, uint8_t x, uint8_t y, uint8_t count)
 * 
 * Puts a string on the device screen at givin position
 * 
 * @param   unsigned char *buffer   The char buffer
 * @param   uint8_t x               The x position
 * @param   uint8_t y               The y position
 * @param   uint8_t count           How many chars will put
 * @return  uint8_t                 How many chars was placed
 */
uint8_t lcd_put_string_at(unsigned char *buffer, uint8_t x, uint8_t y, uint8_t count);

/**
 * void lcd_get_string(unsigned char *buffer, unsigned char x, unsigned char y, uint8_t count)
 * 
 * Gets a string from the device screen, starting at the x, y address
 * 
 * @param   unsigned char *buffer   The char buffer
 * @param   unsigned char x         The x position in the lcd
 * @param   unsigned char y         The y position in the lcd
 * @param   uint8_t count           How many want to read
 */
void lcd_get_string(unsigned char *buffer, unsigned char x, unsigned char y, uint8_t count);

#endif // __SDCC_LCD_STRING_LIBRARY_H__
