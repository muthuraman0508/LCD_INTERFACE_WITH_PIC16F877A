#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h> //main library 
#define _XTAL_FREQ 6000000 // 6 MHz crystal oscillator frequency
void adc_lcd_init(); // function decleartion of adc_lcd_init with no arguments
void adc_read();// function decleartion of adcread with no arguments
void lcd_number_convert(unsigned int i);// function decleartion of lcd_number_convert with an arguments
void lcd_command(unsigned char);// function decleartion of lcd_command with an arguments
void lcd_data(unsigned char);// function decleartion of lcd_data witha an arguments
unsigned int adc_calibrated_data, adc_volt; //declare a varialbe to store the value
unsigned char adc_high, adc_low; //declare a varialbe to store the value

void main(){ //main function which is going to execute 1st
    adc_lcd_init(); //calling the adc_lcd_init function
    while(1){ //wihile with always true condition
        ADCON0 |=0x04; // Start ADC conversion
        while(ADCON0 & 0x04);// Wait for ADC conversion to complete
        adc_high = ADRESH;// Read high 8 bits of ADC result
        adc_low = ADRESL;// Read low 2 bits of ADC result
        adc_volt = (adc_high << 8) + adc_low;//Combine to 10-bit result
        adc_calibrated_data = (adc_volt * 48) / 1024;//Scale ADC to actual value (0 to 47)
        lcd_command(0x80);// Set LCD cursor to beginning of first line
        lcd_number_convert(adc_calibrated_data);// Display the number on the LCD
    }
}

void adc_lcd_init(){
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
  
 adc_read(); //call the adc_read function
}

void lcd_number_convert(unsigned int i){// Converts an integer to characters and displays it on LCD
  int j = 1,s;// j index for array, s single digit holder
  unsigned int n;// Temporary variable for number processing
  unsigned char k[5];// Array to store individual digits
  n = i; // Copy input number to n
  while(n != 0){// Loop until all digits are extracted
     s = (n - (n/10)*10) ;// Get last digit 
     k[j] = s;// Store digit in array
     j++;// Increment array index
     n = n / 10; // Remove last digit from number
  }
  k[j] = '\0';// Null terminate the array
  j--;// Adjust index to last valid digit
  if(k[2] > 0) // If hundreds digit exists
  {
      lcd_command(0x30);// Set cursor to 1st row, 1st column 
      lcd_data(0x30 + k[2]);// Display hundreds digit 
      lcd_command(0x81);// Move cursor to 1st row, 2nd column
      lcd_data(0x30 + k[1]);// Display tens digit
  }
  else {// If no hundreds digit, show space
      lcd_command(0x30);// Set cursor to 1st row, 1st column 
      lcd_data(0x20);// Display space character
      lcd_command(0x81);// Move cursor to 1st row, 2nd column
      lcd_data(0x30 + k[1]);// Display tens digit
  }
  lcd_command(0x82); // Move cursor to 1st row, 3rd column
  lcd_data(0x76);// Display 'v'
}

void lcd_command(unsigned char cmd) {// Sends a command to the LCD to control
    PORTC &= ~0x08; // RS = 0 (command mode) ~8'b00000100
    PORTD = cmd;    // Place command on PORTD
    PORTC |= 0x01;  // Generate Enable pulse (E = 1) 8'b00000001
    PORTC &= ~0x01; // E = 0 ~8'b00000001
    __delay_ms(100); // delay for 100ms
}
void lcd_data(unsigned char data) {
    PORTC |= 0x08;  // RS = 1 (data mode) 8'b00000100
    PORTD = data;   // Send data to LCD
    PORTC |= 0x01;  // Generate Enable pulse (E = 1) 8'b00000001
    PORTC &= ~0x01; // E = 0 8'b00000001
    __delay_ms(100); // delay for 100ms
}

void adc_read(){// Function to configure and initiate ADC
    ADCON1 = 0x8E;// Configure RA0/AN0 as analog input, right justify result
    ADCON0 = 0x81;// Turn ON ADC, select channel AN0
    __delay_ms(10);// Delay to allow acquisition time for stable ADC conversion
}