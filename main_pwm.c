#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>// Include header file for PIC microcontroller
#define _XTAL_FREQ 6000000 // oscillator frequency (6 MHz)
unsigned char pwm_low_20, pwm_high_20; // Declare variables to store duty cycle values of 10%
unsigned char pwm_low_60, pwm_high_60;// Declare variables to store duty cycle values of 50%
unsigned char pwm_low_90, pwm_high_90; // Declare variables to store duty cycle values of 80%
void pwm_config(void);      // Function decleration to initialize pwm signal without argument and without return type
void pwm_cycle(void); // Function decleration to update the dutycycle for pwm signal without argument and without return type
void main(){ // Main function
    pwm_config();   // Call PWM initialization function
    while(1){     // Infinite loop this will execut untill the simulation stops
        pwm_cycle();  // Call function to update PWM duty cycle
    }
}
void pwm_config(void){ // Function definition to initialize PWM signal
    TRISC = 0xFB;  // Configure RC2 as output for CCP1, others as inputs 8'b11111011
    CCP1CON = 0x0C; // Set PWM mode for CCP1 module 8'b00001100
    PR2 = 0x2F;    // Set PWM period (calculated based on desired frequency) 8'b00101111 this is for 2KHz
     /*PR2 = (Fosc / 4 * Fpwm * TMR2_pre_scale_value)
     * where Fosc = 6000000
     * Fpwm = 2KHz
     * TMP@_pre_scale_value  = 16
     */
    T2CON = 0x06;  // Enable Timer2 with pre-scaler 8'b00000110
    // Set duty cycle values for different PWM levels
    /*by the help of the formula which is given in the datasheet we we will get the value of pulse low and high value
     duty_cycle = (((percentage/100)/Pfreq) * 6000000 / 16 )
     * then take the last 2 bit for CCP1CON 4th and 5th bit and remaining bit as LOW
    */
    pwm_high_20 = 0x09; // High byte of 10% duty cycle 8'b00001001
    pwm_low_20 = 0x02;  // separate the last two bits to add in to the CCP1CON 4th and 5th bit 8'b00000010
    pwm_high_60 = 0x1C; // High byte of 50% duty cycle 8'b00011100
    pwm_low_60 = 0x01;  // separate the last two bits to add in to the CCP1CON 4th and 5th bit 8'b00000001
    pwm_high_90 = 0x2A; // High byte of 80% duty cycle 8'b00101010
    pwm_low_90 = 0x01;  // // separate the last two bits to add in to the CCP1CON 4th and 5th bit 8'b00000001
}
void pwm_cycle(void){// Function definition for change PWM duty cycle periodically
    CCPR1 = pwm_high_20; // Load pwm20_high to CCPR1 register for duty cycle 20%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm_low_20 << 4)); // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000ms
    CCPR1 = pwm_high_60; // Load pwm60_high to CCPR1 register for duty cycle 60%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm_low_60 << 4)); // // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000 ms
    CCPR1 = pwm_high_90; // Load pwm90_high to CCPR1 register  for duty cycle 90%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm_low_90 << 4)); // // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000ms
}
