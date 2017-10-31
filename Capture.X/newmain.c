/*
 * File:   newmain.c
 * Author: dmitriy
 *
 * Created on 27 октября 2017 г., 12:21
 */


#include <xc.h>
#pragma config BOREN = ON
#pragma config CPD = OFF
#pragma config FOSC = HS
#pragma config MCLRE = ON
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config LVP = OFF
#pragma config PWRTE = ON


#define LED_INIT TRISAbits.TRISA2 = 0;  TRISAbits.TRISA3 = 0; PORTAbits.RA2 = 0; PORTAbits.RA3 = 0;
#define LED_GREEN_ON PORTAbits.RA2 = 1; PORTAbits.RA3 = 0;
#define LED_RED_ON PORTAbits.RA2 = 0; PORTAbits.RA3 = 1;
#define LED_OFF PORTAbits.RA2 = 0; PORTAbits.RA3 = 0;
#define LED_TOGLE PORTAbits.RA2 ^= 1; PORTAbits.RA3 ^= 1;
#define IN_INIT TRISBbits.TRISB3=1; TRISBbits.TRISB4=1; TRISBbits.TRISB5=1; 


void main(void) {
    
    LED_INIT
    LED_RED_ON
    IN_INIT
    
    //INTCONbits.GIE = 1; //общий флаг разрешения немаскированных прерываний
   // INTCONbits.PEIE = 1;
    
    T1CONbits.TMR1ON = 1; //вкл таймер1
    T1CONbits.TMR1CS = 0; //использовать тактовую частоту системы
    T1CONbits.nT1SYNC = 1; //синхронный режим
    
    T1CONbits.T1OSCEN = 0;
    T1CONbits.T1CKPS0 = 1; //предделитель
    T1CONbits.T1CKPS1 = 1; //предделитель
    
    PIE1bits.TMR1IE = 1; //разрешение прерываний
    PIE1bits.CCP1IE = 1; //разрешение прерываний
    
    PIR1bits.TMR1IF = 1; //флаги прерываний
    PIR1bits.CCP1IF = 0; //флаги прерываний
    
    
    CCP1CONbits.CCP1M = 0b0100; //захват по каждому ниспадающему фронту
    
    
    
    
    while(1)
    {}
    return;
}

void capture (void){
    if(TMR1IF){
        TMR1IF = 0;
    }
    
    if(CCP1IF)
    {
        PIE1bits.CCP1IE = 0;
    LED_TOGLE
        PIE1bits.CCP1IE = 1;
    CCP1IF = 0;
    }

}