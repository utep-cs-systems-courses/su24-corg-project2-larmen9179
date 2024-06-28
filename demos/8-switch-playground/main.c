#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define LED_RED BIT6               // P1.0
#define LED_GREEN BIT0             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2

#define SWITCHES SW1		/* only 1 switch on this board */
#define ALTSWITCHES SW2



void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();
  //buzzer_init();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  P2REN |= ALTSWITCHES;
  P2IE |= ALTSWITCHES;
  P2OUT |= ALTSWITCHES;
  P2DIR &= ~ALTSWITCHES;
  
  or_sr(0x18);  // CPU off, GIE on
} 



void
switch_interrupt_handler()
{
  char p1val = P1IN;
  char p2val = P2IN;/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

  P2IES |= (p2val & ALTSWITCHES);
  P2IES &= (p2val | ~ALTSWITCHES);

/* up=red, down=green */
  
  if (!(p2val & SW2)) {
    light_switch();
  }
}

int lightState = 0;

void
light_switch(){

  //static int lightState = 0;

  /*
  switch(lightState){
  case 0:
    P1OUT &= ~LEDS;
    break;
  case 1:
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    break;
  case 2:
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 3:
    P1OUT |= LEDS;
    break;
  }
  */

  if(lightState == 3)
    lightState = 0;
  else
    lightState++;
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & ALTSWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~ALTSWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

char secondCount = 0;
char interval = 250;

void
__interrupt_vec(WDT_VECTOR) WDT(){

  secondCount++;
  if(secondCount >= interval){
    secondCount = 0;

    blinkSwitch();
    soundSwitch();

  }
}

void
blinkSwitch(){

  switch(lightState){
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
soundSwitch(){
  switch(lightState){
  case 0:
    //buzzer_set_period(5000);
    break;
  case 1:
    //buzzer_set_period(6000);
    break;
  case 2:
    //buzzer_set_period(7000);
    break;
  case 3:
    //buzzer_set_period(8000);
    break;
  }
}
