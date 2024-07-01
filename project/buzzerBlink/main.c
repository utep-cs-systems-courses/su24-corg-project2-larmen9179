#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "main.h"
#include "song.h"

#define LED_RED BIT6               // P1.0
#define LED_GREEN BIT0             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT0		/* switch1 is p1.3 */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES SW1		/* only 1 switch on this board */
#define ALTSWITCHES (SW1 | SW2 | SW3 | SW4)



void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();
  buzzer_init();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
  
  P2REN |= ALTSWITCHES;
  P2IE |= ALTSWITCHES;
  P2OUT |= ALTSWITCHES;
  P2DIR &= ~ALTSWITCHES;
  
  or_sr(0x18);  // CPU off, GIE on
} 

//global var to control state for system
char globalState = 0;

void
switch_interrupt_handler()
{
  char p2val = P2IN;/* other 4 switches are in P2 */
/* update switch interrupt sense to detect changes from current buttons */
  /* if switch up, sense down */
  /* if switch down, sense up */

  P2IES |= (p2val & ALTSWITCHES);
  P2IES &= (p2val | ~ALTSWITCHES);

/* up=red, down=green */
  //If any switch is pressed, switch state
  if (!(p2val & SW1)){
    globalState = 0;
  }
  else if (!(p2val & SW2)){
    globalState = 1;
  }
  else if (!(p2val & SW3)){
    globalState = 2;
  }
  else if (!(p2val & SW4)){
    globalState = 3;
  }
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & ALTSWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~ALTSWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

char secondCountBlink = 0;
char secondCountSound = 0;
char interval = 250;

void
__interrupt_vec(WDT_VECTOR) WDT(){

  secondCountBlink++;
  secondCountSound++;
  if(secondCountBlink >= interval){
    secondCountBlink = 0;

    lightSwitch();

  }
  if(secondCountSound >= 27){
    secondCountSound = 0;
    soundSwitch(globalState);
  }
  
}

/*changes leds and led speed based off light state, called during interrupts from system*/
void
lightSwitch(){

  switch(globalState){
  case 0:
    P1OUT &= ~LEDS;
    interval = 125;
    break;
  case 1:
    P1OUT &= ~LED_GREEN;
    P1OUT ^= LED_RED;
    interval = 62;
    break;
  case 2:
    P1OUT &= ~LED_RED;
    P1OUT ^= LED_GREEN;
    interval = 31;
    break;
  case 3:
    P1OUT ^= LEDS;
    interval = 15;
    break;
  }
  
}


void
soundSwitch(char option){

  if(option == 0){
    songOne();
  }
  else if(option == 1){
    songTwo();
  }
  else if(option == 2){
    songThree();
  }
  else if(option == 3){
    songFour();
  }
}
