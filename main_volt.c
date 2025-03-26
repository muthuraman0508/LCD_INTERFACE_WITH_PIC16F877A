#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h> //header file
#define _XTAL_FREQ 6000000// oscilator with 6MHz
void lcd_data(unsigned char);// lcd_data function declaration
void lcd_command(unsigned char);// lcd_cmd function declaration
void lcd_output(float);// lcd_output function declaration
void lcd_delay(unsigned int);// lcd_delay function declaration
void keyScan();// keyScan function declaration
void init(); // lcd_init function declaration
unsigned char text[10] = {"BATT VOLT:"}; //creating unsigned character variable for batt voltage
unsigned char status_low[11] = {"BATTERY LOW"};//creating unsigned character variable for low status
unsigned char status_medium[14] = {"BATTERY MEDIUM"};//creating unsigned character variable for medium status
unsigned char status_high[12] = {"BATTERY HIGH"};//creating unsigned character variable for high status
float voltage = 17.6; //declare default value in the variable
unsigned char d1, d2, d3; //creating unsigned char variable
void main(){ //main block which is going to execute 1st
    init(); //calling init function with no argument
    while(1){ //while loop will execute un till the condition false
        keyScan(); //calling keyScan function with no argument
    }
}
void init(){ //init function definition
    TRISC = 0x00; //set PORTC as output 0 -> output, 1 -> input
    TRISD = 0x00; //set PORTD as output 0 -> output, 1 -> input
    TRISB = 0xF0;//set PORTB as input RD4-RB7 0 -> output, 1 -> input
    OPTION_REG &= 0x7F; //enable the internal pull up resistor
    PORTB = 0x00; //set all the initial value of PORT B as low
     lcd_command(0x30);// calling the lcd_command function with 0x30 as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x30);// calling the lcd_command function with 0x30 as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x30);// calling the lcd_command function with 0x30 as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x38);// calling the lcd_command function with 0x38 as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x06);// calling the lcd_command function with 0x06 as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x0C);// calling the lcd_command function with 0x0C as argument, this line is use to configure the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
    lcd_command(0x01);// calling the lcd_command function with 0x01 as argument, this line is use to clar the display
    __delay_ms(100);// delay for 100 ms by calling the delay function
}
void keyScan(){ //keyScan function definition
    unsigned char value = PORTB; //assign thePORTB data in to the value
    switch(value){ //initiate the switch case
        case 0xE0: //checking the case match with condition
            lcd_command(0x01);// calling the lcd_command function with 0x01 as argument, this line is use to clear the display
            lcd_command(0x80); // setting the initial position the top row by calling lcd_command with one argument
            for(int i = 0; i < 10; i++){//for loop for print the text in the top row
                lcd_data(text[i]); //printing the text in the display one by one
            }
            lcd_output(voltage); //print the voltage value by calling lcd_output function with voltage value
            lcd_command(0xC0);//set the courser in the second row for print the status
    if (voltage >= 15.5 && voltage <= 17.5) { //checking the condition for display status
            for(int j = 0; j < 11; j++){ //for loop for print the status one by one
                lcd_data(status_low[j]); //print the status of the voltage in the display
            }
    } else if (voltage > 17.5 && voltage <= 20.5) {//checking the condition for display status
            for(int k = 0; k < 14; k++){//for loop for print the status one by one
                lcd_data(status_medium[k]);//print the status of the voltage in the display
            }
    } else if (voltage > 20.5 && voltage <= 22.5) {//checking the condition for display status
            for(int l = 0; l < 12; l++){//for loop for print the status one by one
                lcd_data(status_high[l]);//print the status of the voltage in the display
            }
    }
            break; //once all done break the loop and getting out from the case condition
        case 0xD0://checking the case match with condition
            lcd_command(0x01);// calling the lcd_command function with 0x01 as argument, this line is use to clear the display
            lcd_command(0x80);// setting the initial position the top row by calling lcd_command with one argument
            for(int i = 0; i < 10; i++){ //for loop for print the text in the top row
                lcd_data(text[i]);//printing the text in the display one by one
            }
            voltage += 0.1; //increment the voltage value by 0.1
            if(voltage > 22.5){ //check the condition for range
                voltage = 22.5; //limit the value with 22.5 
            }
            lcd_command(0x8A); //set the courser to print the voltage value
            lcd_output(voltage);//print the voltage value by calling lcd_output function with voltage value
            lcd_command(0xC0);//set the courser in the second row for print the status
    if (voltage >= 15.5 && voltage <= 17.5) {//checking the condition for display status
            for(int j = 0; j < 11; j++){//for loop for print the status one by one
                lcd_data(status_low[j]);//print the status of the voltage in the display
            }
    } else if (voltage > 17.5 && voltage <= 20.5) {//checking the condition for display status
            for(int k = 0; k < 14; k++){//for loop for print the status one by one
                lcd_data(status_medium[k]);//print the status of the voltage in the display
            }
    } else if (voltage > 20.5 && voltage <= 22.5) {//checking the condition for display status
            for(int l = 0; l < 12; l++){//for loop for print the status one by one
                lcd_data(status_high[l]);//print the status of the voltage in the display
            }
    }
            break;//once all done break the loop and getting out from the case condition
        case 0xB0://checking the case match with condition
            lcd_command(0x01);// calling the lcd_command function with 0x01 as argument, this line is use to clear the display
            lcd_command(0x80);// setting the initial position the top row by calling lcd_command with one argument
            for(int i = 0; i < 10; i++){//for loop for print the text in the top row
                lcd_data(text[i]);//printing the text in the display one by one
            }
            voltage -= 0.1;//decrement the voltage value by 0.1
            if(voltage < 15.5){//check the condition for range
                voltage = 15.5;//limit the value with 15.5 
            }
            lcd_command(0x8A);//set the courser to print the voltage value
            lcd_output(voltage);//print the voltage value by calling lcd_output function with voltage value
            lcd_command(0xC0);//set the courser in the second row for print the status
    if (voltage >= 15.5 && voltage <= 17.5) {//checking the condition for display status
            for(int j = 0; j < 11; j++){//for loop for print the status one by one
                lcd_data(status_low[j]);//print the status of the voltage in the display
            }
    } else if (voltage > 17.5 && voltage <= 20.5) {//checking the condition for display status
            for(int k = 0; k < 14; k++){//for loop for print the status one by one
                lcd_data(status_medium[k]);//print the status of the voltage in the display
            }
    } else if (voltage > 20.5 && voltage <= 22.5) {//checking the condition for display status
            for(int l = 0; l < 12; l++){//for loop for print the status one by one
                lcd_data(status_high[l]);//print the status of the voltage in the display
            }
    }
            break;//once all done break the loop and getting out from the case condition
        case 0x70://checking the case match with condition
            lcd_command(0x01);// calling the lcd_command function with 0x01 as argument, this line is use to clear the display
            lcd_command(0x80);// setting the initial position the top row by calling lcd_command with one argument
            for(int i = 0; i < 10; i++){//for loop for print the text in the top row
                lcd_data(text[i]);//printing the text in the display one by one
            }
            voltage = 17.6; //set the default value if the reset pressed
            lcd_command(0x8A);//set the courser to print the voltage value
            lcd_output(voltage);//print the voltage value by calling lcd_output function with voltage value
            lcd_command(0xC0);//set the courser in the second row for print the status
    if (voltage >= 15.5 && voltage <= 17.5) {//checking the condition for display status
            for(int j = 0; j < 11; j++){//for loop for print the status one by one
                lcd_data(status_low[j]);//print the status of the voltage in the display
            }
    } else if (voltage > 17.5 && voltage <= 20.5) {//checking the condition for display status
            for(int k = 0; k < 14; k++){//for loop for print the status one by one
                lcd_data(status_medium[k]);//print the status of the voltage in the display
            }
    } else if (voltage > 20.5 && voltage <= 22.5) {//checking the condition for display status
            for(int l = 0; l < 12; l++){//for loop for print the status one by one
                lcd_data(status_high[l]);//print the status of the voltage in the display
            }
    }
            break;//once all done break the loop and getting out from the case condition       
    }   
}
void lcd_command(unsigned char i){
    PORTC &= ~0x08;  // clear the bit (0) for command mode
    PORTD = i;       // assign the PORTD value
    PORTC |= 0x01;   // set the enable bit
    PORTC &= ~0x01;  // clear the enable pin
    __delay_ms(100); // 100 ms delay
}
void lcd_data(unsigned char i){
    PORTC |= 0x08;   // set the bit (1) for data mode
    PORTD = i;       // assign the PORTD value
    PORTC |= 0x01;   // set the enable bit
    PORTC &= ~0x01;  // clear the enable pin
    __delay_ms(100); // 100 ms delay
}
void lcd_output(float voltage){ //lcd_output function definition
    d1 = (unsigned char)(voltage / 10) + '0'; //sperate the voltage value by single unit and change it to character
    d2 = (unsigned char)((int)voltage % 10) + '0';//sperate the voltage value by single unit and change it to character
    d3 = (unsigned char)((int)(voltage * 10) % 10) + '0';//sperate the voltage value by single unit and change it to character
    lcd_data(d1); //calling the lcd_data function with one argument d1
    lcd_data(d2);//calling the lcd_data function with one argument d2
    lcd_data('.');//calling the lcd_data function with one argument .
    lcd_data(d3);//calling the lcd_data function with one argument d3
    lcd_data('V');//calling the lcd_data function with one argument V
}