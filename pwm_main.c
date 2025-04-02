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
unsigned char pwm10_low, pwm10_high; // Declare variables to store duty cycle values of 10%
unsigned char pwm50_low, pwm50_high;// Declare variables to store duty cycle values of 50%
unsigned char pwm80_low, pwm80_high; // Declare variables to store duty cycle values of 80%
void pwm_init(void);      // Function decleration to initialize pwm signal without argument and without return type
void pwm_dutycycle(void); // Function decleration to update the dutycycle for pwm signal without argument and without return type
void main(){ // Main function
    pwm_init();   // Call PWM initialization function
    while(1){     // Infinite loop this will execut untill the simulation stops
        pwm_dutycycle();  // Call function to update PWM duty cycle
    }
}
void pwm_init(void){ // Function definition to initialize PWM signal
    TRISC = 0xFB;  // Configure RC2 as output for CCP1, others as inputs 8'b11111011
    CCP1CON = 0x0C; // Set PWM mode for CCP1 module 8'b00001100
    PR2 = 0x5E;    // Set PWM period (calculated based on desired frequency) 8'b01011110
    T2CON = 0x06;  // Enable Timer2 with prescaler 8'b00000110
    // Set duty cycle values for different PWM levels
    pwm10_high = 0x09; // High byte of 10% duty cycle 8'b00001001
    pwm10_low = 0x02;  // saparate the last two bits to add in to the CCP!CON 4th and 5th bit 8'b00000010
    pwm50_high = 0x2F; // High byte of 50% duty cycle 8'b00101111
    pwm50_low = 0x00;  // separate the last two bits to add in to the CCP!CON 4th and 5th bit 8'b00000000
    pwm80_high = 0x48; // High byte of 80% duty cycle 8'b01001000
    pwm80_low = 0x00;  // // separate the last two bits to add in to the CCP!CON 4th and 5th bit 8'b00000000
}
void pwm_dutycycle(void){// Function definition for change PWM duty cycle periodically
    CCPR1 = pwm10_high; // Load pwm10_high to CCPR1 register for duty cycle 10%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm10_low << 4)); // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000ms
    CCPR1 = pwm50_high; // Load pwm50_high to CCPR1 register for duty cycle 50%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm50_low << 4)); // // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000ms
    CCPR1 = pwm80_high; // Load pwm80_high to CCPR1 register  for duty cycle 80%
    CCP1CON = ((CCP1CON & 0xCF) | (pwm80_low << 4)); // // set the CCP1CON 4th and 5th bit from the CCPR1L register
    __delay_ms(3000); // delay for 3000ms
}
