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
#define ALTSWITCHES (SW2 | SW3 | SW4 | SW1)

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
  if (!(p2val & SW2) || !(p2val & SW3) || !(p2val & SW4) || !(p2val & SW1)) {
    light_switch();
  }
}

//global var to control light state
int lightState = 0;

//method to switch states for other functions
void
light_switch(){
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

/*changes leds and led speed based off light state, called during interrupts from system*/
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
    buzzer_set_period(5000);
    break;
  case 1:
    buzzer_set_period(6000);
    break;
  case 2:
    buzzer_set_period(7000);
    break;
  case 3:
    buzzer_set_period(8000);
    break;
  }
}
