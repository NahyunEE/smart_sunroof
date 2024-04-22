#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LCD_H
#define LCD_H

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command
#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line
#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off
#define ENABLE  0b00000100 // Enable bit

extern int fd;
extern int fd_lcd;


void lcd_init();
void typeFloat(float myFloat);
void typeInt(int i);
void ClrLcd(void);
void lcdLoc(int line);
void typeChar(char val);
void typeln(const char* s);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void updateLCD(int mode, int safe_state, int speed, int bright);

#endif