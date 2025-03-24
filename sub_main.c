#pragma config FOSC = EXTRC // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF  // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF  // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF    // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF    // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF    // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF     // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>                                 //header file
#define _XTAL_FREQ 6000000                      // oscilator with 6MHz
void lcd_init(void);                                // lcd_init function declaration
void lcd_cmd(unsigned char);                // lcd_cmd function declaration
void lcd_data(unsigned char);                   // lcd_data function declaration
void delay(unsigned int);                       // delay function declaration
void lcd_display(unsigned int);                  // lcd_display function declaration
unsigned char x, a[5], equal, plus, minus;             // creating unsigned character variable
unsigned int data1, data2, value, delayCount, m, n; // creating unsigned integer variables

void main(void) // main function which is going to execute 1st
{
    lcd_init();            // init function calling this will go to the line number and come back to this line
    data1 = 200;        // assign the  value to the data1 variable
    data2 = 100;        // assign the  value to the data2 variable
    equal = '=';       // assign the  value to the equal variable
    plus = '+';        // assign the  value to the plus variable
    minus = '-';
    lcd_cmd(0x80); // calling the lcd_cmd function with 0x80 as argument, this line is use to set the position of the LCD display
    lcd_display(data1);  // calling the lcd_display function with data1 as argument, this line is use to print the data1 value in the display
    lcd_cmd(0x83); // calling the lcd_cmd function with 0x83 as argument, this line is use to set the position of the LCD display
    lcd_data(minus);    // calling the lcd_data function with plus as argument, this line is use to print the plus symbol in the display
    lcd_cmd(0x84); // calling the lcd_cmd function with 0x84 as argument, this line is use to set the position of the LCD display
    lcd_display(data2);  // calling the lcd_display function with data2 as argument, this line is use to print the data2 value in the display
    lcd_cmd(0x87); // calling the lcd_cmd function with 0x87 as argument, this line is use to set the position of the LCD display
    lcd_data(equal);   // calling the lcd_data function with equal as argument, this line is use to print the equal symbol in the display
    if(data1 > data2){ // checking conditon for symbol
        lcd_cmd(0x88); // calling the lcd_cmd function with 0x88 as argument, this line is use to set the position of the LCD display
        lcd_data(plus); // calling the lcd_data function with equal as argument, this line is use to print the plus symbol in the display
        value = data1 - data2; // sub the data1 and data2 and assign the value in to the value variable
        lcd_cmd(0x89);// calling the lcd_cmd function with 0x89 as argument, this line is use to set the position of the LCD display
       lcd_display(value);   // calling the lcd_display function with value as argument, this line is use to print the output in the display
    } else{ //if the condition false it will come to this line
        lcd_cmd(0x88); // calling the lcd_cmd function with 0x88 as argument, this line is use to set the position of the LCD display
        lcd_data(minus);// calling the lcd_data function with equal as argument, this line is use to print the minus symbol in the display
        value = data2 - data1; // add the data1 and data2 and assign the value in to the sum variable
        lcd_cmd(0x89);// calling the lcd_cmd function with 0x89 as argument, this line is use to set the position of the LCD display
        lcd_display(value);   // calling the lcd_display function with value as argument, this line is use to print the output in the display
    }    
    while (1)          // this line will execute un till the simulation stops
        ;
}
void lcd_init(void) // init function definition with void return type and no argument
{
    TRISC = 0x00;      // set the direction of PORTC as output 0-> output 1-> input
    TRISD = 0x00;      // set the direction of PORTD as output 0-> output 1-> input
    lcd_cmd(0x30); // calling the lcd_cmd function with 0x30 as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x30); // calling the lcd_cmd function with 0x30 as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x30); // calling the lcd_cmd function with 0x30 as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x38); // calling the lcd_cmd function with 0x38 as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x06); // calling the lcd_cmd function with 0x06 as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x0C); // calling the lcd_cmd function with 0x0C as argument, this line is use to configure the display
    delay(100);        // delay for 100 ms by calling the delay function
    lcd_cmd(0x01); // calling the lcd_cmd function with 0x01 as argument, this line is use to clear the display
    delay(100);        // delay for 100 ms by calling the delay function
}
void lcd_display(unsigned int i) // lcd_display function declaration with one argument and void return type
{
    unsigned char s, x = 1; // declare a unsigned character variables
    m = i;                  // assign argument variable as m
    while (m != 0)          // this will execute untill the last digit was arrived
    {
        s = m - ((m / 10) * 10); // getting the single digit
        a[x] = s;                // store the digit in array
        x++;                     // increment the array index by one
        m = m / 10;              // get the quotient value
    }
    a[x] = '\0';   // making null the remaining index
    x -= 1;        // decrement the index value by one
    while (x != 0) // check un till the last index
    {
        n = 0x30 + a[x]; // add with 0x03 to get the suitable ASCII value of the numbers
        lcd_data(n);     // calling the lcd_data function with n as argument to display it in the display
        x--;             // decrement the index value
    }
}
void lcd_cmd(unsigned char i) // lcd_cmd function declaration with one argument and no return type
{
    PORTC &= ~0x08;  // clear the bit (0) for cmd mode
    PORTD = i;       // assign the PORTD value
    PORTC |= 0x01;   // set the enable bit
    PORTC &= ~0x01;  // clear the enable pin
    __delay_ms(100); // 100 ms delay
}
void lcd_data(unsigned char i) // lcd_cmd function declaration with one argument and no return type
{
    PORTC |= 0x08;   // set the bit (1) for data mode
    PORTD = i;       // assign the PORTD value
    PORTC |= 0x01;   // set the enable bit
    PORTC &= ~0x01;  // clear the enable pin
    __delay_ms(100); // 100 ms delay
}
void delay(unsigned int delayCount) // delay function declaration with one argument and no return type
{
    while (--delayCount) // decrement by one till the condition false
        ;
}