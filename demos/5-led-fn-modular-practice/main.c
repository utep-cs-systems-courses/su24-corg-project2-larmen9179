//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT = LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}

void redControl(int on)
{
  if (on) {
    P1OUT |= LED_RED;
  } else {
    P1OUT &= ~LED_RED;
  }
}


// blink state machine
static int blinkLimit = 8;   //  state var representing reciprocal of duty cycle
static int blinkLimitTwo = 0;
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state

  static int blinkCountTwo = 0;
  blinkCount ++;
  blinkCountTwo ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
  }
  else{
    greenControl(0);
  }
  if(blinkCountTwo >= blinkLimitTwo){
    blinkCountTwo = 0;
    redControl(1);
  }
  else{
    redControl(0);
  }
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;
  blinkLimitTwo --;// reduce duty cycle
  if (blinkLimit >= 8){  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
  }
  if (blinkLimitTwo <= 0){
    blinkLimitTwo = 8;
  }
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 62) { // once each second
    secondCount = 0;
    oncePerSecond();
  } }

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}


void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 

