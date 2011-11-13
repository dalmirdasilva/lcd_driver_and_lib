/**
 * SDCC - PIC drivers
 * 
 * lcd.h
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __SDCC_LCD_DRIVER_H__
#define __SDCC_LCD_DRIVER_H__ 1

/*
 * Lcd status info
 */
uint8_t lcd_status_info = 0;// 0b00000000
                            //   ||||||||_ Timeout on write operation
                            //   |||||||__ Unused
                            //   ||||||___ Unused
                            //   |||||____ Unused
                            //   |||______ Unused
                            //   ||_______ Unused
                            //   |________ Unused

/*
 * Control mode
 */
enum lcd_control_mode_t {
    LCD_CONTROL_MODE_ON = 1,
    LCD_CONTROL_MODE_BLINK = 2,
    LCD_CONTROL_MODE_UNDERLINE = 4
};

/*
 * Entry mode
 */
enum lcd_entry_mode_t {
    LCD_ENTRY_MODE_INCREMENT = 1,
    LCD_ENTRY_MODE_MOVE_AUTOMATICALY = 2
};

/*
 * Shift mode
 */
enum lcd_shift_mode_t {
    LCD_SHIFT_MODE_DISPLAY = 1,
    LCD_SHIFT_MODE_RIGHT = 2
};

/*
 * Command                   Binary                             Hex
 *                           D7  D6  D5  D4  D3  D2  D1  D0 
 * Clear Display              0   0   0   0   0   0   0   1     01
 * Display & Cursor Home      0   0   0   0   0   0   1   x     02 or 03
 * Character Entry Mode       0   0   0   0   0   1   1/D S     04 to 07
 * Display On/Off & Cursor    0   0   0   0   1   D   U   B     08 to 0F
 * Display/Cursor Shift       0   0   0   1  D/C R/L  x   x     10 to 1F
 * Function Set               0   0   1 8/4  2/1 10/7 x   x     20 to 3F
 * Set CGRAM Address          0   1   A   A   A   A   A   A     40 to 7F
 * Set Display Address        1   A   A   A   A   A   A   A     80 to FF
 * 
 * 1/D: 1=Increment*, 0=Decrement 
 * S: 1=Display shift on, 0=Off* 
 * D: 1=Display on, 0=Off* 
 * U: 1=Cursor underline on, 0=Off* 
 * B: 1=Cursor blink on, 0=Off* 
 * D/C: 1=Display shift, 0=Cursor move 
 * R/L: 1=Right shift, 0=Left shift 
 * 8/4: 1=8-bit interface*, 0=4-bit interface 
 * 2/1: 1=2 line mode, 0=1 line mode* 
 * 10/7: 1=5x10 dot format, 0=5x7 dot format* 
 * 
 * x = Don't care 
 * * = Initialization settings 
 */
enum lcd_cmd_t {
    LCD_CMD_CLEAR_DISPLAY = 0x01,
    LCD_CMD_DISPLAY_CURSOR_HOME = 0x02,
    LCD_CMD_ENTRY_MODE = 0x04,
    LCD_CMD_DISPLAY_CONTROL = 0x08,
    LCD_CMD_DISPLAY_SHIFT = 0x10,
    LCD_CMD_FUNCTION_SET = 0x20,
    LCD_CMD_SET_CGRAM_ADDRESS = 0x40,
    LCD_CMD_SET_DISPLAY_ADDRESS = 0x80
};
#define LCD_CMD_ENTRY_MODE_MOVE_AUTOMATICALY 0x01
#define LCD_CMD_ENTRY_MODE_INCREMENT 0x02
#define LCD_CMD_DISPLAY_CONTROL_ON 0x04
#define LCD_CMD_DISPLAY_CONTROL_UNDERLINE 0x02
#define LCD_CMD_DISPLAY_CONTROL_BLINK 0x01
#define LCD_CMD_DISPLAY_SHIFT_DISPLAY 0x08
#define LCD_CMD_DISPLAY_SHIFT_RIGHT 0x04
#define LCD_CMD_FUNCTION_SET_8BIT_INTERFACE 0x10
#define LCD_CMD_FUNCTION_SET_2LINE_MODE 0x08
#define LCD_CMD_FUNCTION_SET_5x10_DOT_FORMAT 0x04

#define LCD_TYPE                         0x02
#define LCD_SECOND_LINE_ADDR             0x40

/*
 * Pin 4 is the Register Select (RS) line, the first of the
 * three command control inputs. When this line is low, data bytes transferred to the display
 * are treated as commands, and data bytes read from the display indicate its status. By
 * setting the RS line high, character data can be transferred to and from the module.
 */
enum lcd_rs_t {
    LCD_RS_COMMAND = 0,
    LCD_RS_DATA = 1
};

/*
 * Pin 6 is the Enable (E) line. This input is used to initiate the actual transfer of commands
 * or character data between the module and the data lines. When writing to the display,
 * data is transferred only on the high to low transition of this signal. However, when
 * reading from the display, data will become available shortly after the low to high
 * transition and remain available until the signal falls low again.
 */
enum lcd_en_t {
    LCD_EN_LOW = 0,
    LCD_EN_HIGH = 1
};

/*
 * Pin 5 is the Read/Write (R/W) line. This line is pulled low in order to write commands or
 * character data to the module, or pulled high to read character data or status information
 * from its registers.
 */
enum lcd_rw_t {
    LCD_RW_WRITE = 0,
    LCD_RW_READ = 1
};

#define lcd_en_tris(x) (TRISBbits.TRISB0 = (x))
#define lcd_rw_tris(x) (TRISBbits.TRISB1 = (x))
#define lcd_rs_tris(x) (TRISBbits.TRISB2 = (x))

#define lcd_en_pin (PORTBbits.RB0)
#define lcd_rw_pin (PORTBbits.RB1)
#define lcd_rs_pin (PORTBbits.RB2)

#define lcd_tris4 (TRISBbits.TRISB4)
#define lcd_tris5 (TRISBbits.TRISB5)
#define lcd_tris6 (TRISBbits.TRISB6)
#define lcd_tris7 (TRISBbits.TRISB7)

#define lcd_pin4 (PORTBbits.RB4)
#define lcd_pin5 (PORTBbits.RB5)
#define lcd_pin6 (PORTBbits.RB6)
#define lcd_pin7 (PORTBbits.RB7)

#define lcd_tris_set(nibble) do {  \
    lcd_tris4 = ((nibble) & 0x01); \
    lcd_tris5 = ((nibble >> 1) & 0x01); \
    lcd_tris6 = ((nibble >> 2) & 0x01); \
    lcd_tris7 = ((nibble >> 3) & 0x01); \
} while(0)

#define lcd_bus_write(nibble) do { \
    lcd_pin4 = ((nibble) & 0x01);  \
    lcd_pin5 = ((nibble >> 1) & 0x01);  \
    lcd_pin6 = ((nibble >> 2) & 0x01);  \
    lcd_pin7 = ((nibble >> 3) & 0x01);  \
} while(0)

#define lcd_bus_read() (PORTB >> 4)

#define lcd_is_busy(status) (status & 0x80)
#define lcd_busy_address(status) (status & 0x7f)

#define lcd_info_set_write_timeout() (lcd_status_info |= 0x01)
#define lcd_info_get_write_timeout() (lcd_status_info | 0x01)
#define lcd_info_reset_write_timeout() (lcd_status_info &= 0xfe)

void lcd_init();

void lcd_init_io();

void lcd_clear();

unsigned char lcd_read(enum lcd_rs_t rs);

uint8_t lcd_write(unsigned char chr, enum lcd_rs_t rs, uint8_t timeout);

uint8_t lcd_status();

void lcd_command(enum lcd_cmd_t cmd);

void lcd_send_nibble(uint8_t nibble);

void lcd_entry(enum lcd_entry_mode_t mode);

void lcd_shift(enum lcd_shift_mode_t mode);

void lcd_position(uint8_t x, uint8_t y);

void lcd_on();

void lcd_off();

void lcd_control(enum lcd_control_mode_t mode);

#endif // __SDCC_LCD_DRIVER_H__
