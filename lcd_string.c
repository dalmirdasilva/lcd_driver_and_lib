/**
 * SDCC - PIC libraries
 * 
 * lcd_string.c
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __SDCC_LCD_STRING_LIBRARY_C__
#define __SDCC_LCD_STRING_LIBRARY_C__ 1

#include <lcd_string.h>

/**
 * void lcd_put_char(unsigned char c)
 * 
 * Puts a char at pre-specified position
 * 
 * @param   unsigned char c     The char to be writed
 * @return  void
 */
void lcd_put_char(unsigned char c) {
    switch(c) {
        case '\f':
            lcd_clear();
        break;
        case '\n':
        case '\r':
            lcd_position(0, 1);
        break;
        default:
            lcd_write(c, LCD_RS_DATA, 2);
    }
}

/**
 * uint8_t lcd_put_string(unsigned char *buffer, uint8_t count)
 * 
 * Retrieves a char from the lcd device at pre-specified position
 * 
 * @param   unsigned char x     The x position in the lcd
 * @param   unsigned char y     The y position in the lcd
 * @return  unsigned char       The read char
 */
unsigned char lcd_get_char(unsigned char x, unsigned char y) {
    lcd_position(x, y);
    return (unsigned char) lcd_read(LCD_RS_DATA);
}

/**
 * void lcd_put_string(char *buffer, uint8_t count)
 * 
 * Puts a string on the device screen
 * 
 * @param   unsigned char *buffer   The char buffer
 * @param   uint8_t count           How many chars will put
 * @return  uint8_t                 How many chars could not be placed
 */
uint8_t lcd_put_string(unsigned char *buffer, uint8_t count) {
    while(*buffer != '\0' && count--) {
        lcd_put_char(*buffer++);
    }
    return count;
}

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
uint8_t lcd_put_string_at(unsigned char *buffer, uint8_t x, uint8_t y, uint8_t count) {
    lcd_position(x, y);
    return lcd_put_string(buffer, count);
}

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
void lcd_get_string(unsigned char *buffer, unsigned char x, unsigned char y, uint8_t count) {
    uint8_t i = 0;
    while(count--) {
        buffer[i] = lcd_get_char(x, y);
        i++;
        x++;
        if(x == LCD_SECOND_LINE_ADDR) {
            x = 0;
            y++;
        }
    }
    buffer[i] = '\0';
}

#endif // __SDCC_LCD_STRING_LIBRARY_C__
