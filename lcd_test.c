
void lcd_test_position() {
    lcd_clear();
    lcd_position(1, 0);
    lcd_write(0xff, LCD_RS_DATA, 10);
    delay_ms(250);
    lcd_position(1, 1);
    lcd_write(0xff, LCD_RS_DATA, 10);
    delay_ms(250);
    lcd_position(5, 0);
    lcd_write(0xff, LCD_RS_DATA, 10);
    delay_ms(250);
    lcd_position(5, 1);
    lcd_write(0xff, LCD_RS_DATA, 10);
    delay_ms(250);
}

void lcd_test_fill_all() {
    uint8_t x, y;
    lcd_clear();
    // Fill slowling
    for(x = 0; x < 16; x++) {
        for(y = 0; y < 2; y++) {
            lcd_position(x, y);
            lcd_write(0xff, LCD_RS_DATA, 10);
            delay_ms(150);
        }
    }
    lcd_clear();
    // Fill fastly
    for(x = 0; x < 16; x++) {
        for(y = 0; y < 2; y++) {
            lcd_position(x, y);
            lcd_write(0xff, LCD_RS_DATA, 10);
        }
    }
}

void lcd_test_reading_after_write() {
    uint8_t x, y;
    char c = 'a';
    lcd_clear();
    // Write some letters at the first line
    for(x = 0; x < 16; x++) {
        lcd_position(x, 0);
        lcd_write(c++, LCD_RS_DATA, 10);
        delay_ms(250);
    }
    // Read in the reverse order and rewrite at the second line
    for(x = 0; x < 16; x++) {
        lcd_position(x, 0);
        c = lcd_read(LCD_RS_DATA);
        lcd_position(15 - x, 1);
        lcd_write(c, LCD_RS_DATA, 10);
        delay_ms(250);
    } 
}
void lcd_test_shift() {
    uint8_t x;
    char c = 'a';
    lcd_clear();
    lcd_position(9, 0);
    lcd_command(LCD_CMD_ENTRY_MODE);
    for(x = 0; x < 9; x++) {
        lcd_write('0'+ x, LCD_RS_DATA, 10);
        delay_ms(150);
    } 
    lcd_position(9, 1);
    for(x = 0; x < 9; x++) {
        lcd_write('9'- x, LCD_RS_DATA, 10);
        delay_ms(150);
    }
    lcd_clear();
    lcd_command(LCD_CMD_ENTRY_MODE | LCD_CMD_ENTRY_MODE_MOVE_AUTOMATICALY | LCD_CMD_ENTRY_MODE_INCREMENT);
    lcd_position(15, 0);
    for(x = 0; x < 15; x++) {
        lcd_write('0' + x, LCD_RS_DATA, 10);
        delay_ms(150);
    }
    lcd_clear();
    lcd_position(15, 1);
    for(x = 0; x < 15; x++) {
        lcd_write('0' + x, LCD_RS_DATA, 10);
        delay_ms(150);
    }
    lcd_command(LCD_CMD_ENTRY_MODE);
    lcd_clear();
}

void lcd_test_do() {
    lcd_clear();
    lcd_write('p', LCD_RS_DATA, 10);
    lcd_write('o', LCD_RS_DATA, 10);
    lcd_write('s', LCD_RS_DATA, 10);
    delay_ms(1000);
    lcd_test_position();
    lcd_clear();
    delay_ms(1000);
    lcd_write('s', LCD_RS_DATA, 10);
    lcd_write('h', LCD_RS_DATA, 10);
    lcd_write('i', LCD_RS_DATA, 10);
    lcd_write('f', LCD_RS_DATA, 10);
    lcd_write('t', LCD_RS_DATA, 10);
    delay_ms(1000);
    lcd_test_shift();
    lcd_clear();
    delay_ms(2000);
    lcd_write('f', LCD_RS_DATA, 10);
    lcd_write('i', LCD_RS_DATA, 10);
    lcd_write('l', LCD_RS_DATA, 10);
    lcd_write('l', LCD_RS_DATA, 10);
    delay_ms(1000);
    lcd_test_fill_all();
    lcd_clear();
    delay_ms(2000);
    lcd_write('r', LCD_RS_DATA, 10);
    lcd_write('d', LCD_RS_DATA, 10);
    lcd_write('&', LCD_RS_DATA, 10);
    lcd_write('w', LCD_RS_DATA, 10);
    lcd_write('t', LCD_RS_DATA, 10);
    delay_ms(1000);
    lcd_test_reading_after_write();
}

