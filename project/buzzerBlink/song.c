#include "song.h"
#include "buzzer.h"

//Normal Notes
#define NOTE_C4 3822 * 2
#define NOTE_D4 3405 * 2
#define NOTE_E4 3034 * 2
#define NOTE_F4 2863 * 2
#define NOTE_G4 2551 * 2
#define NOTE_A4 2273 * 2
#define NOTE_B4 2024 * 2

//Sharps
#define NOTE_CS4 3608 * 2
#define NOTE_DS4 3214 * 2
#define NOTE_FS4 2703 * 2
#define NOTE_GS4 2408 * 2
#define NOTE_AS4 2145 * 2

//Flats
#define NOTE_DB4 3608 * 2
#define NOTE_EB4 3214 * 2
#define NOTE_GB4 2408 * 2
#define NOTE_AB4 2145 * 2
#define NOTE_BB4 1911 * 2

void songOne(){
  static char songState = 0;

  switch(songState){
  case 0:
  case 1:
    buzzer_set_period(NOTE_C4);
    break;
  case 2:
  case 6:
  case 7:
  case 3:
    buzzer_set_period(NOTE_E4);
    break;
  case 4:
  case 5:
    buzzer_set_period(NOTE_F4);
    break;
  case 8:
    buzzer_set_period(NOTE_C4);
    break;
  case 9:
    buzzer_set_period(0);
    break;
  case 10:
    buzzer_set_period(NOTE_C4);
    break;
  case 11:
    buzzer_set_period(NOTE_E4);
    break;
  case 12:
    buzzer_set_period(NOTE_E4);
    break;
  case 13:
    buzzer_set_period(NOTE_F4);
    break;
  case 14:
    buzzer_set_period(NOTE_F4);
    break;
  case 15:
    buzzer_set_period(NOTE_E4);
    break;
  case 16:
    buzzer_set_period(NOTE_E4);
    break;
  }

  if(songState == 16)
    songState = 0;
  else
    songState++;
}

void songTwo(){
  static char songState = 0;

  switch(songState){
  case 0:
  case 1:
  case 2:
  case 3:
    buzzer_set_period(NOTE_A4 * 2);
    break;
  case 4:
  case 5:
  case 6:
  case 7:
    buzzer_set_period(NOTE_E4);
    break;
  case 8:
  case 9:
  case 10:
  case 11:
    buzzer_set_period(NOTE_A4 * 2);
    break;
  case 12:
  case 13:
  case 14:
  case 15:
    buzzer_set_period(NOTE_E4);
    break;
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
    buzzer_set_period(NOTE_F4);
    break;
  case 24:
  case 25:
  case 26:
  case 27:
    buzzer_set_period(NOTE_A4 * 2);
    break;
  case 28:
  case 29:
  case 30:
  case 31:
    buzzer_set_period(NOTE_E4);
    break;
  case 32:
  case 33:
  case 34:
  case 35:
    buzzer_set_period(NOTE_A4 * 2);
    break;
  case 36:
  case 37:
  case 38:
  case 39:
    buzzer_set_period(NOTE_E4);
    break;
  case 40:
  case 41:
  case 42:
  case 43:
  case 44:
  case 45:
  case 46:
  case 47:
    buzzer_set_period(NOTE_D4);
    break;
  }
  

  if(songState == 47)
    songState = 0;
  else
    songState++;
}

void songThree(){
  static char songState = 0;

  switch(songState){
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  }

  if(songState == 3)
    songState == 0;
  else
    songState++;
}

void songFour(){
  buzzer_set_period(0);
}


