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

void lcd_data(unsigned char);
void lcd_command(unsigned char);
void lcd_output(unsigned int);
void lcd_delay(unsigned int);
void keyScan();
void init();
unsigned char arr[15] = {"SET SPD:    rpm"};
unsigned char value, d4, d3, d2, d1;
unsigned int x, j = 0;
void main(){
    init();
    while(1){
        keyScan();
    }
}
void init(){
    TRISC =0x00;
    TRISD =0x00;
    TRISB = 0xF0;
    OPTION_REG &= 0x7F;
    PORTB = 0x00;
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x38);
    __delay_ms(100);
    lcd_command(0x06);
    __delay_ms(100);
    lcd_command(0x0C);
    __delay_ms(100);
    lcd_command(0x01);
    __delay_ms(100);
}
void keyScan(){
    value = PORTB;
    switch(value){
        case 0xE0:
            lcd_command(0x80);
            for(x = 0; x<8; x++){
              lcd_data(arr[x]);
            }
            lcd_command(0x8c);
            for(x = 12; x<15 ; x++){
                lcd_data(arr[x]);
            }
            lcd_command(0x88);
            lcd_output(j);
            break;
        case 0xD0:
            j++;
            if(j > 5000){
                j = 5000;
            }
            lcd_command(0x88);
            lcd_output(j);
            break;
        case 0xB0:
            j--;
            if(j<1){
                j = 1;
            }
            lcd_command(0x88);
            lcd_output(j);
            break;
        case 0x70:
            j = 0;
            lcd_command(0x88);
            lcd_output(j);
            break;         
            
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
void lcd_output(unsigned int i){
    d4 = (unsigned char)(i/1000);
    d3 = (unsigned char)((i - (d4*1000))/100);
    d2 = (unsigned char)((i - (d4*1000) - (d3*100))/10);
    d1 = (unsigned char)((i - d4*1000) - (d3*100) - (d2*10));
    lcd_command(0x88);
    lcd_data(0x30 + d4);
    lcd_command(0x89);
    lcd_data(0x30 + d3);
    lcd_command(0x8A);
    lcd_data(0x30 + d2);
    lcd_command(0x8B);
    lcd_data(0x30 + d1);
}
