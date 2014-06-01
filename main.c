// PIC16F873A MIDI Synth

#include <xc.h>

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include "main.h"

void main() {
	// Disable Interrupts
	INTCONbits.GIE = 0;

	// Clear PORTs
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;

    // Switch to bank 1
    STATUSbits.RP1 = 0;
	STATUSbits.RP0 = 1;

    // Disable ADC
    ADCON1 = 0x06;

    // Disable comparator
	CMCONbits.CM0 = 1;
	CMCONbits.CM1 = 1;
	CMCONbits.CM2 = 1;

    // Disable T0CKI pin
    OPTION_REGbits.T0CS = 0;

    // set PORT directions
	TRISA = 0;					// Set all to output
	TRISB = 0;
	TRISC = 0;

	TRISCbits.TRISC7 = 1;		// RC7/RX set to input

    // Switch to bank 0
    STATUSbits.RP0 = 0;

    // Clear PORTs
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;

	/*; Setup USART MIDI Reception
	movlw	FIFO_BOTTOM
	movwf	fifo_bottom
	movwf	fifo_top
	bsf		fifo_empty,0
	clrf	note
	clrf	data_wait

    bcf     STATUS,RP1			; Switch to bank 1
    bsf     STATUS,RP0

	movlw	9					; 31250 baud
	movwf	SPBRG				; set baud rate generator

	bcf		TXSTA,SYNC			; clear SYNC

	bcf     STATUS,RP0			; back to bank 0

	bsf		RCSTA,SPEN			; set SPEN

	; Switch to bank 1
    bcf     STATUS,RP1
    bsf     STATUS,RP0
	bsf		PIE1,RCIE			; enable interrupt on byte RC
	; Switch to bank 0
    bcf     STATUS,RP0*/

	INTCONbits.GIE = 1;			// global interrupt enable
	INTCONbits.PEIE = 1;		//peripheral interrupt enable
	
//	bsf		RCSTA,CREN			; set CREN to enable reception


	// Main Loop
	for (;;) {
		// Toggle RA0
		PORTA = PORTA ^ 1;
		countDelay(80, 1);
	}
}

void countDelay(int count1, int count2) {
	int x = 0;
	while(count2--) {
		while(count1--) {
			x+1;				// perform addition and discard result. aka: nop
		}
	}
}
