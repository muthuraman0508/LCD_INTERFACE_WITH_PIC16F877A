#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
void init(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void delay(unsigned int);
void lcd_output(unsigned int);
unsigned char j, k[5],equal, plus;
unsigned int num1, num2, sum, delayCount, m, n;

void main(void) {
    init();
    num1 = 423;
    num2 = 375;
    equal = '=';
    plus = '+';
    lcd_command(0x80);
    lcd_output(num1);
    lcd_command(0x83);
    lcd_data(plus);
    lcd_command(0x84);
    lcd_output(num2);
    lcd_command(0x87);
    lcd_data(equal);
    lcd_command(0x88);
    sum = num1 + num2;
    lcd_output(sum);
    while(1);
}
void init(void){
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_command(0x30);
    delay(100);
    lcd_command(0x30);
    delay(100);    
    lcd_command(0x30);
    delay(100);    
    lcd_command(0x38);
    delay(100);    
    lcd_command(0x06);
    delay(100);
    lcd_command(0x0C);
    delay(100);
    lcd_command(0x01);
    delay(100);
}
void lcd_output(unsigned int i){
    unsigned char s, j=1;
    m=i;
    while(m != 0){
        s = m-((m/10)*10);
        k[j] = s;
        j++;
        m = m/10;
    }
    k[j] = '\0';
    j -= 1;
    while(j != 0) {
        n=0x30 + k[j];
        lcd_data(n);
        j--;
    }
}
void lcd_command(unsigned char i){
   PORTC &= ~0x08;
   PORTD = i;
   PORTC |= 0x01;
   PORTC &= ~0x01;
   __delay_ms(100);
}
void lcd_data(unsigned char i){
    PORTC |= 0x08;
   PORTD = i;
   PORTC |= 0x01;
   PORTC &= ~0x01;
   __delay_ms(100);
}
void delay(unsigned int delayCount){
    while(--delayCount);
}