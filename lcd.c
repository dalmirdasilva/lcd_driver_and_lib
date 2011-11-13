/**
 * SDCC - PIC drivers
 * 
 * lcd.c
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#include <lcd.h>

#ifndef __SDCC_LCD_DRIVER_C__
#define __SDCC_LCD_DRIVER_C__ 1

/*
 * General Initialization	Example Initialization
 * 1	Wait 20ms for LCD to power up
 * 2	Write D7-4 = 3 hex, with RS = 0
 * 3	Wait 5ms
 * 4	Write D7-4 = 3 hex, with RS = 0, again
 * 5	Wait 200us
 * 6	Write D7-4 = 3 hex, with RS = 0, one more time
 * 7	Wait 200us
 * 8	Write D7-4 = 2 hex, to enable four-bit mode
 * 9	Wait 5ms
 * 10	Write Command "Set Interface"	Write 28 hex (4-Bits, 2-lines)
 * 11	Write Command "Enable Display/Cursor"	Write 08 hex (don't shift display, hide cursor)
 * 12	Write Command "Clear and Home"	Write 01 hex (clear and home display)
 * 13	Write Command "Set Cursor Move Direction"	Write 06 hex (move cursor right)
 * 14	--	Write 0C hex (turn on display)
 * Display is ready to accept data.
 */
void lcd_init() {
    uint8_t count;
    lcd_init_io();
    delay_ms(20);
    lcd_rs_pin = LCD_RS_COMMAND;
    lcd_rw_pin = LCD_RW_WRITE;
    lcd_en_pin = LCD_EN_LOW;
    for(count = 0; count < 3; count++) {
        lcd_send_nibble(0x03);
        delay_ms(5);
    }
    lcd_send_nibble(0x02);
    delay_ms(5);
    lcd_command(LCD_CMD_FUNCTION_SET | LCD_CMD_FUNCTION_SET_2LINE_MODE);
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_CMD_DISPLAY_CONTROL_ON| LCD_CMD_DISPLAY_CONTROL_BLINK | LCD_CMD_DISPLAY_CONTROL_UNDERLINE);
    lcd_command(LCD_CMD_CLEAR_DISPLAY);
    lcd_command(LCD_CMD_ENTRY_MODE | LCD_CMD_ENTRY_MODE_INCREMENT);
}

void lcd_init_io() {
    lcd_en_tris(0);
    lcd_rw_tris(0);
    lcd_rs_tris(0);
    lcd_tris_set(0);
}

void lcd_clear() {
    lcd_command(LCD_CMD_CLEAR_DISPLAY);
}

unsigned char lcd_read(enum lcd_rs_t rs) {
    unsigned char chr;
    lcd_tris_set(0xff);
    lcd_rs_pin = rs;
    lcd_rw_pin = LCD_RW_READ;
    lcd_en_pin = LCD_EN_LOW;
    delay_us(1);
    lcd_en_pin = LCD_EN_HIGH;
    delay_us(60);
    chr = lcd_bus_read();
    chr <<= 4;
    lcd_en_pin = LCD_EN_LOW;
    delay_us(1);
    lcd_en_pin = LCD_EN_HIGH;
    delay_us(60);
    chr |= lcd_bus_read();
    lcd_en_pin = LCD_EN_LOW;
    return chr;
}

uint8_t lcd_write(unsigned char chr, enum lcd_rs_t rs, uint8_t timeout) {
    unsigned char status;
    do {
        status = lcd_status();
    } while(lcd_is_busy(status) && timeout--);
    if(lcd_is_busy(status)) {
        lcd_info_set_write_timeout();
        return 0;
    }
    lcd_tris_set(0x00);
    lcd_en_pin = LCD_EN_LOW;
    lcd_rs_pin = rs;
    lcd_rw_pin = LCD_RW_WRITE;
    lcd_send_nibble(chr >> 4);
    lcd_send_nibble(chr);
    return 1;
}

uint8_t lcd_status() {
    return lcd_read(LCD_RS_COMMAND);
} 

void lcd_command(enum lcd_cmd_t cmd) {
    lcd_write(cmd, LCD_RS_COMMAND, 0xff);
}

void lcd_send_nibble(uint8_t nibble) {
    lcd_en_pin = LCD_EN_HIGH;
    lcd_bus_write(nibble);
    delay_us(60);
    lcd_en_pin = LCD_EN_LOW;
}

void lcd_entry(enum lcd_entry_mode_t mode) {
    uint8_t cmd = LCD_CMD_ENTRY_MODE;
    if(mode & LCD_ENTRY_MODE_MOVE_AUTOMATICALY) {
        cmd |= LCD_CMD_ENTRY_MODE_MOVE_AUTOMATICALY;
    }
    if(mode & LCD_ENTRY_MODE_INCREMENT) {
        cmd |= LCD_CMD_ENTRY_MODE_INCREMENT;
    }
    lcd_command(cmd);
}

void lcd_shift(enum lcd_shift_mode_t mode) {
    uint8_t cmd = LCD_CMD_DISPLAY_SHIFT;
    if(mode & LCD_SHIFT_MODE_DISPLAY) {
        cmd |= LCD_CMD_DISPLAY_SHIFT_DISPLAY;
    }
    if(mode & LCD_SHIFT_MODE_RIGHT) {
        cmd |= LCD_CMD_DISPLAY_SHIFT_RIGHT;
    }
    lcd_command(cmd);
}

void lcd_position(uint8_t x, uint8_t y) {
    uint8_t cmd = LCD_CMD_SET_DISPLAY_ADDRESS;
    if(y == 1) {
        x += LCD_SECOND_LINE_ADDR;
    }
    cmd |= x;
    lcd_command(cmd);
}

void lcd_on() {
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_CMD_DISPLAY_CONTROL_ON);
}

void lcd_off() {
    lcd_command(LCD_CMD_DISPLAY_CONTROL);
}

void lcd_control(enum lcd_control_mode_t mode) {
    uint8_t cmd = LCD_CMD_DISPLAY_CONTROL;
    if(mode & LCD_CONTROL_MODE_ON) {
        cmd |= LCD_CMD_DISPLAY_CONTROL_ON;
    }
    if(mode & LCD_CONTROL_MODE_UNDERLINE) {
        cmd |= LCD_CMD_DISPLAY_CONTROL_UNDERLINE;
    }
    if(mode & LCD_CONTROL_MODE_BLINK) {
        cmd |= LCD_CMD_DISPLAY_CONTROL_BLINK;
    }
    lcd_command(cmd);
}

#endif // __SDCC_LCD_DRIVER_C__
