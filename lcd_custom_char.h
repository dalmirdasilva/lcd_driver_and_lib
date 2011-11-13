/**
 * SDCC - PIC drivers
 * 
 * lcd_custom_char.h
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __SDCC_LCD_DRIVER_H__
    #error The lcd driver must be included.
#endif

#ifndef __SDCC_LCD_CUSTOM_CHAR_H__
#define __SDCC_LCD_CUSTOM_CHAR_H__ 1

/*
    int8_t i = 0;
    char custom_chars[] = {
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x00,
        
        0x00, 0x00, 0x0e, 0x0a,
        0x0e, 0x00, 0x00, 0x00,
        
        0x00, 0x1f, 0x11, 0x11,
        0x11, 0x1f, 0x00, 0x00
    };
    lcd_custom_char_create(custom_chars, 0, 3);
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_CMD_DISPLAY_CONTROL_ON);
    while(1) {
        lcd_position(0, 0);
        lcd_write(i++ % 3, LCD_RS_DATA, 2);
        delay_ms(150);
    }
 */ 

void lcd_custom_char_create(uint8_t buffer[8], uint8_t address, uint8_t count);

#endif // __SDCC_LCD_CUSTOM_CHAR_H__
