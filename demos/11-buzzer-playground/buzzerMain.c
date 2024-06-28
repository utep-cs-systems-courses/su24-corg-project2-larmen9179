#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
    enableWDTInterrupts();
 
    buzzer_init();	/* start buzzing!!! 2MHz/1000 = 2kHz*/


    or_sr(0x18);          // CPU off, GIE on
}

char secondCount = 0;
long cycles = 5000000;


void
__interrupt_vec(WDT_VECTOR) WDT(){

  secondCount++;
  if(secondCount >= 62){
    secondCount = 0;

    soundSwitch();
  }
  
}

void soundSwitch(){

  if(cycles >= 1400000){
    cycles = 4000000;
  }

  
  cycles += 1000000;
  
  buzzer_set_period(cycles);

  
  
}
