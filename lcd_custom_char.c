/**
 * SDCC - PIC drivers
 * 
 * lcd_custom_char.c
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __SDCC_LCD_DRIVER_H__
    #error The lcd driver must be included.
#endif

#ifndef __SDCC_LCD_CUSTOM_CHAR_C__
#define __SDCC_LCD_CUSTOM_CHAR_C__ 1

void lcd_custom_char_create(uint8_t buffer[], uint8_t address, uint8_t count) {
    uint8_t i;
    lcd_command(LCD_CMD_SET_CGRAM_ADDRESS | address * 8);
    delay_ms(1);
    for (i = 0; i < count * 8; i++) {
        lcd_write(buffer[i], LCD_RS_DATA, 10);
        delay_ms(1);
    }
    lcd_command(LCD_CMD_DISPLAY_CURSOR_HOME);
}

#endif // __SDCC_LCD_CUSTOM_CHAR_C__
