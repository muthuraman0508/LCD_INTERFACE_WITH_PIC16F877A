#include <xc.h>
#define _XTAL_FREQ 6000000

// CONFIG
#pragma config FOSC = EXTRC, WDTE = OFF, PWRTE = OFF, BOREN = OFF
#pragma config LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

// LCD Function Prototypes
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init();
void lcd_display_number_CH1(unsigned int num);
void lcd_display_number_CH4(unsigned int num);
unsigned char adc_high, adc_low; //declare a varialbe to store the value
unsigned long int adc_calibrated_data, adc_volt; //declare a varialbe to store the value
unsigned long int raw_data;
void main() {
    TRISC = 0x00;   // Control lines
    TRISD = 0x00;   // Data lines
    PORTC = 0x00;
    PORTD = 0x00;
    lcd_init();
    while (1) {
        ADCON1 = 0x84;
        ADCON0 = 0x89;
        __delay_ms(2);        // Acquisition delay
        ADCON0 |= 0x04;       // Start conversion
        while (ADCON0 & 0x04); // Wait for conversion complete
        raw_data = (ADRESH << 8) + ADRESL;  // Combine 10-bit result
        __delay_ms(100);
        ADCON1 = 0x82;
        ADCON0 = 0xA1;
        ADCON0 |=0x04; // Start ADC conversion
        while(ADCON0 & 0x04);// Wait for ADC conversion to complete
        adc_high = ADRESH;// Read high 8 bits of ADC result
        adc_low = ADRESL;// Read low 2 bits of ADC result
        adc_volt = (adc_high << 8) + adc_low;//Combine to 10-bit result
        adc_calibrated_data = (adc_volt * 135) / 1024;//Scale ADC to actual value (0 to 135)
        lcd_command(0x80);// Set LCD cursor to beginning of first line
        lcd_display_number_CH4(adc_calibrated_data);// Display the number on the LCD

        // --- Display CH1 on first row ---
        lcd_command(0x80);
        lcd_data('C');
        lcd_data('H');
        lcd_data('1');
        lcd_data(':');
        lcd_command(0x84);
        lcd_display_number_CH1(raw_data);
        lcd_data('V');

        // --- Display CH4 on second row ---
        lcd_command(0xC0);
        lcd_data('C');
        lcd_data('H');
        lcd_data('4');
        lcd_data(':');
        lcd_command(0xC4);
        lcd_display_number_CH4(adc_calibrated_data);
        lcd_data('V');

        __delay_ms(500);
    }
}

void lcd_display_number_CH1(unsigned int num) {
     unsigned char d1 = (num / 1000) % 10;
    unsigned char d2 = (num / 100) % 10;
    unsigned char d3 = (num / 10) % 10;
    unsigned char d4 = num % 10;

    if (num >= 1000) {
        lcd_data(d1 + '0');
        lcd_data(d2 + '0');
        lcd_data(d3 + '0');
        lcd_data(d4 + '0');
    } else if (num >= 100) {
        lcd_data(' ');
        lcd_data(d2 + '0');
        lcd_data(d3 + '0');
        lcd_data(d4 + '0');
    } else if (num >= 10) {
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(d3 + '0');
        lcd_data(d4 + '0');
    } else {
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(d4 + '0');
    }
}
void lcd_display_number_CH4(unsigned int num) {
     unsigned char d1 = (num / 100) % 10;
    unsigned char d2 = (num / 10) % 10;
    unsigned char d3 = num % 10;

    if (num >= 100) {
        lcd_data(d1 + '0');
        lcd_data(d2 + '0');
        lcd_data(d3 + '0');
    } else if (num >= 10) {
        lcd_data(' ');
        lcd_data(d2 + '0');
        lcd_data(d3 + '0');
    }
    else {
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(d3 + '0');
    }
}

void lcd_command(unsigned char cmd) {
    PORTC &= ~0x08;  // RS = 0
    PORTD = cmd;
    PORTC |= 0x01;   // EN = 1
    __delay_ms(2);
    PORTC &= ~0x01;  // EN = 0
    __delay_ms(2);
}

void lcd_data(unsigned char data) {
    PORTC |= 0x08;   // RS = 1
    PORTD = data;
    PORTC |= 0x01;   // EN = 1
    __delay_ms(2);
    PORTC &= ~0x01;  // EN = 0
    __delay_ms(2);
}

void lcd_init() {
  TRISC = 0x00;   // Set PORTC as output (for LCD control) 0'b00000000
  TRISD = 0x00;   // Set PORTD as output (for LCD data)0'b00000000
  PORTC = 0x00;   //set the initial value of all pin as low
  PORTD = 0x00;   //set the initial value of all pin as low
  lcd_command(0x30); // LCD Initialization by sending 0x30 as argument
  __delay_ms(100); // delay for 100 ms
  lcd_command(0x30);// LCD Initialization by sending 0x30 as argument
  __delay_ms(100);// delay for 100 ms
  lcd_command(0x30);// LCD Initialization by sending 0x30 as argument
  __delay_ms(100);// delay for 100 ms
  lcd_command(0x38);// LCD Initialization by sending 0x38 as argument for 8-bit mode, 2-line display
  __delay_ms(100); // delay for 100 ms 
  lcd_command(0x06);// LCD Initialization by sending 0x06 as argument for Entry mode set, auto-increment cursor
  __delay_ms(100); // delay for 100 ms
  lcd_command(0x0C);// LCD Initialization by sending 0x0C as argument for Display ON, Cursor OFF
  __delay_ms(100); // delay for 100 ms
  lcd_command(0x01);// LCD Initialization by sending 0x01 as argument for Clear display
  __delay_ms(100); // delay for 100 ms
}
