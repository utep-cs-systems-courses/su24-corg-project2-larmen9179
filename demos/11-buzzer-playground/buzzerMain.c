#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

//Normal Notes
#define NOTE_C4 3822
#define NOTE_D4 3405
#define NOTE_E4 3034
#define NOTE_F4 2863
#define NOTE_G4 2551
#define NOTE_A4 2273
#define NOTE_B4 2024

//Sharps
#define NOTE_CS4 3608
#define NOTE_DS4 3214
#define NOTE_FS4 2703
#define NOTE_GS4 2408
#define NOTE_AS4 2145

//Flats
#define NOTE_DB4 3608
#define NOTE_EB4 3214
#define NOTE_GB4 2408
#define NOTE_AB4 2145
#define NOTE_BB4 1911

int main() {
    configureClocks();
    enableWDTInterrupts();
 
    buzzer_init();	/* start buzzing!!! 2MHz/1000 = 2kHz*/


    or_sr(0x18);          // CPU off, GIE on
}

char secondCount = 0;
int cycles = 0;


void
__interrupt_vec(WDT_VECTOR) WDT(){

  secondCount++;
  if(secondCount >= 62){
    secondCount = 0;

    soundSwitch();
  }
  
}

char note = 0;

void soundSwitch(){

  switch(note){
  case 0:
  case 1:
  case 2:
  case 4:
      buzzer_set_period(NOTE_EB4);
      break;
  case 3:
      buzzer_set_period(NOTE_B4);
      break;
  case 5:
    buzzer_set_period(NOTE_GB4);
    break;
  case 6:
    buzzer_set_period(NOTE_G4);
    break;
  }

  if(note == 6){
    note = 0;
  }
  else{
    note++;
  }
}
