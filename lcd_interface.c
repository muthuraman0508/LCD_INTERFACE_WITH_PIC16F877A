#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
#define _XTAL_FREQ 6000000
void init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned char x,i,m;
unsigned char array[12] = {"HELLO WORLD"};

void main(void) {
    init();
    lcd_command(0x80);
    for(x = 0;x<11;x++){
        lcd_data(array[x]);
    }
    while(1);
}
void init(){
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x38);
    __delay_ms(100);
    lcd_command(0x0C);
    __delay_ms(100);
    lcd_command(0x01);
    __delay_ms(100);
    lcd_command(0x06);
    __delay_ms(100);
}
void lcd_command(unsigned char i){
    RC3 = 0;
    PORTD = i;
    RC0 = 1;
    __delay_ms(100);
    RC0 = 0;    
}

void lcd_data(unsigned char i){
    RC3 = 1;
    PORTD = i;
    RC0 = 1;
    __delay_ms(100);
    RC0 = 0;
    
}
