/*
 * LCDFunctions.c
 *
 * Created: 2014-12-01 12:26:00
 * Author: Michael Nilsson och Ola Dahl
 */

#include "asf.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"

int setupLCD(void) /* Ställer in display för första användning */
{
	int all_ok = 0; /*antar inget fungerar*/
	
	LCDwrite(0b00001000, LOW);		/* Display off */
	LCDwrite(0b00000001, LOW);		/* Display clear */
	
	delay(3000);
	
	LCDwrite(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	LCDwrite(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */
	
	all_ok = 1;
	return all_ok; /*returnerar 1 om allt är ok.*/
}

void printLetter(uint32_t adc_value) /* Skriver ut vilken knapp som är intryckt */
{
	
	if( ((adc_value - 100) <= UP) && ( (adc_value + 100) >= UP ) ){
		LCDwrite('U', HIGH);
		LCDwrite('P', HIGH);
	}
	
	if(adc_value == RIGHT){
		LCDwrite('R', HIGH);
		LCDwrite('I', HIGH);
		LCDwrite('G', HIGH);
		LCDwrite('H', HIGH);
		LCDwrite('T', HIGH);
	}
	
	if( ((adc_value - 100) <= DOWN) && ( (adc_value + 100) >= DOWN ) ){
		LCDwrite('D', HIGH);
		LCDwrite('O', HIGH);
		LCDwrite('W', HIGH);
		LCDwrite('N', HIGH);
	}
	
	if( ((adc_value - 100) <= LEFT) && ( (adc_value + 100) >= LEFT ) ){
		LCDwrite('L', HIGH);
		LCDwrite('E', HIGH);
		LCDwrite('F', HIGH);
		LCDwrite('T', HIGH);
	}
	
	if( ((adc_value - 100) <= SELECT) && ( (adc_value + 100) >= SELECT ) ){
		LCDwrite('S', HIGH);
		LCDwrite('E', HIGH);
		LCDwrite('L', HIGH);
		LCDwrite('E', HIGH);
		LCDwrite('C', HIGH);
		LCDwrite('T', HIGH);
	}
	
	if(adc_value > 3000){
		LCDwrite('N', HIGH);
		LCDwrite('O', HIGH);
		LCDwrite(' ', HIGH);
		LCDwrite('I', HIGH);
		LCDwrite('N', HIGH);
		LCDwrite('P', HIGH);
		LCDwrite('U', HIGH);
		LCDwrite('T', HIGH);
	}
}

void printNumber(uint32_t adc_value) /* Skriver ut värdet från AD-omvandlare */
{
	uint32_t tusental = (adc_value / 1000);
	uint32_t hundratal = (adc_value % 1000) / 100;
	uint32_t tiotal = (adc_value % 100) / 10;
	uint32_t ental = (adc_value % 10);
	
	LCDwrite(' ', HIGH);
	LCDwrite(tusental + 0x30, HIGH);
	LCDwrite(hundratal + 0x30, HIGH);
	LCDwrite(tiotal + 0x30, HIGH);
	LCDwrite(ental + 0x30, HIGH);
}

void clearDisplay(void) /* Tömmer displayen */
{
	LCDwrite(0b00000001, LOW); //Tömmer display
}

int LCDInit(void)		/* Initializes the display on the LCD shield, returns 1 if everything is ok */
{
	int all_ok=0;		/* at the beginning assume nothing works */
	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(4100);	/* wait for more than 4,1 ms */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);

	delay(100);	/* wait 100 us */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);		
	
	delay(100);	/* wait 100 us */
		
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);

	LCDwrite(0b00101000, LOW);		/* Two rows, small font */
	LCDwrite(0b00001000, LOW);		/* Display off */
	LCDwrite(0b00000001, LOW);		/* Display clear */
	
	delay(3000);
	
	LCDwrite(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	LCDwrite(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */

	all_ok = 1;					/* simple return statement showing that the initialization of the LCD has completed */
	return all_ok;
}


uint8_t LCDwrite(uint8_t byte, bool type)		/* writes a byte to the LCD display */
/*
 *	writes the byte (8 bits) to the LCD display as two consecutive 4 bits 
 *	type = 0 controls the display
 *	type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
 *
 *	LCDwrite returns the actual pinout value on PIOC 26-23, which is the reverse order compared to the Due pin order of D4-D7
 */
{
	/* In it's infinite wisdom the shield has the data pins in mirrored order compared to the Due board */
	uint8_t mirror_pin[16]={0b0000,0b1000,0b0100,0b1100,0b0010,0b1010,0b0110,0b1110,0b0001,0b1001,0b0101,0b1101,0b0011,0b1011,0b0111,0b1111};
	uint32_t byte32;
	uint8_t byte_orig;
	uint8_t mirrored_output = 0;

	byte_orig = byte;

	/* write the first 4 bits to the shield. */
	byte = byte>>4;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte << 23;
	mirrored_output = byte<<4;
	
	ioport_set_pin_level(LCD_RS, type); 
	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);
	
	/* write the second 4 bits to the shield. */
	byte = byte_orig;
	byte = byte & 0x0f;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte<<23;
	mirrored_output = mirrored_output + byte;

	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay(100);
	
	return mirrored_output;
}

