/*
 * LCDFunctions.h
 *
 * Created: 2014-12-01 12:26:00
 * Author: Michael Nilsson och Ola Dahl
 */


#ifndef LCDFunctions_h
#define LCDFunctions_h

#include "asf.h" /* Ugly to include an h-file in another h-file, but necessary */
#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define LCD_mask_D4_D7 0b00000111100000000000000000000000

/* Definerar värden för knappar på display */
#define UP 530
#define RIGHT 0
#define DOWN 1200
#define LEFT 1800
#define SELECT 2430

int setupLCD(void);
void printLetter(uint32_t acd_value);
void printNumber(uint32_t nbr);
void clearDisplay(void);

int LCDInit(void);
uint8_t LCDwrite(uint8_t byte, bool type);
void ClearLCDDisplay(void);
#endif
