#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h> //in build library
#define _XTAL_FREQ 6000000 //use clock frequency as 6MHz
void display_init(); //display_init function decleration without argument
void display_cmd(unsigned char);//display_command function decleration with argument
void display_data(unsigned char);//display_data function decleration with argument
unsigned char data[11] = {"MUTHU RAMAN"};//store the MUTHU RAMANN in the array with the size of 11(0 to 10)
unsigned char i, j, k, d, cmd;//declare variable as unsigned character
void main(void) { //main block which will execute 1st
    display_init();//display_init function call this will move to the line number 44 of my code once it over it came back here
    display_cmd(0x82);//display_cmd function call this will move to the line number 30 in my code and come back here
                        //once it is over
    for(i = 0; i<11;i++){//for loop is used to move the index of array from 0  to 10
        display_data(data[i]);//calling the display_data function line number 37 for every index value and return back to the same line when over
    }
    __delay_ms(1000);//1000 ms delay for clear visiblity
    for(j = 0, k = 0xCD; j < 11; j++, k--){ //in this for loop we are increment the data by index and decrement the courser position by value
        display_cmd(k); //calling the display_cmd function with argument as position
        display_data(data[j]); // calling the display_data function with argument as value in the index
    }
    while(1);// once all process completed it will continously run un till the simulation stops
}
void display_cmd(unsigned char cmd){//display_cmd definition with one argument, this line is called in the line 18 and 25
    RC3 = 0;//set RS as command mode
    PORTD = cmd;//send the command through the PPORT D
    RC0 = 1;//enable the LCD by making it high
    __delay_ms(100);//100 ms delay
    RC0 = 0;// disable the LCD by making it as LOW
}
void display_data(unsigned char d){//display_data definition with one argument, this line is called in line number 21 and 26
    RC3 = 1;//set RS as data mode
    PORTD = d;//send the command through the PPORT D
    RC0 = 1;//enable the LCD by making it high
    __delay_ms(100);//100 ms delay
    RC0 = 0;// disable the LCD by making it as LOW
}
void display_init(){//display_init function definition with no argument this line is called in line number 17
    TRISC = 0x00;//declare all the PORT C as output 0 -> output, 1 -> input
    TRISD = 0x00;//declare all the PORT D as output 0 -> output, 1 -> input
    //LCD configuration as per the data sheet
    display_cmd(0x30);//LCD configuration as per the data sheet
    __delay_ms(100);//100 ms delay
    display_cmd(0x30);//LCD configuration as per the data sheet
    __delay_ms(100);//100 ms delay
    display_cmd(0x30); //initialization LCD as per the data sheet by calling display_cmd function with one argument
    __delay_ms(100);//100 ms delay
    display_cmd(0x38);//initialization LCD as per the data sheet by calling display_cmd function with one argument
    __delay_ms(100);//100 ms delay
    display_cmd(0x0C);//initialization LCD as per the data sheet by calling display_cmd function with one argument->display ON courser OFF
    __delay_ms(100);//100 ms delay
    display_cmd(0x01);//initialization LCD as per the data sheet by calling display_cmd function with one argument->clear display
    __delay_ms(100);//100 ms delay
}
//clean and build