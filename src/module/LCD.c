#include "LCD.h"
#include "mode.h"

void lcd_init() {
    // Initialise display
    lcd_byte(0x33, LCD_CMD); // Initialise
    lcd_byte(0x32, LCD_CMD); // Initialise
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
    lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD); // Clear display
    delayMicroseconds(500);
}

void typeFloat(float myFloat) {
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    typeln(buffer);
}

// int to string
void typeInt(int i) {
    char array1[20];
    sprintf(array1, "%d", i);
    typeln(array1);
}

// clr lcd go home loc 0x80
void ClrLcd(void) {
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int line) {
    lcd_byte(line, LCD_CMD);
}

// out char to LCD at current position
void typeChar(char val) {

    lcd_byte(val, LCD_CHR);
}


// this allows use of any size string
void typeln(const char* s) {

    while (*s) lcd_byte(*(s++), LCD_CHR);

}

void lcd_byte(int bits, int mode) {

    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    // High bits
    wiringPiI2CReadReg8(fd_lcd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd_lcd, bits_low);
    lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits) {
    // Toggle enable pin on LCD display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd_lcd, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd_lcd, (bits & ~ENABLE));
    delayMicroseconds(500);
}


void updateLCD(int mode, int safe_state, int speed, int bright) {
    // 모드에 따라 LCD의 첫 번째 라인에 메시지를 출력.
    lcdLoc(LINE1);
    if(safe_state){
      typeln("MODE: SAFE                   ");
    }
    else{
      switch (mode) {
        case USER_MODE:
            typeln("MODE: USER                  ");
            break; 
        case CLEAN_MODE :
            typeln("MODE: CLEAN                  ");
            break;
        case BRIGHT_MODE:
            typeln("MODE: BRIGHT                  ");
            break;
        default:
            typeln("MODE: UNKNOWN                ");
            break;
        }
    }
    // LCD의 두 번째 라인에 속도와 밝기 값을 출력.
    lcdLoc(LINE2);
    typeln("SP:");
    typeInt(speed);
    typeln(" BR:");
    typeInt(bright);
}