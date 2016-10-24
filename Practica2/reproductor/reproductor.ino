#include "pitches.h"

/* Variables que controlan si se está en modo play(1) o plause(0) y la nota por la que va tocando actualmente.  */

int isplaying = 1;
int thisNote = 0;

const int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};

const int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

/* Declaración del pin4 para el Buzzer. */

const int BUZZER = 4;

/* Tamaño de la canción. */
const int size = sizeof(melody) / sizeof(int);

/* Declaración del pin del altavoz y de la interrupción que maneja el botón de play/pause en el pin número 2.*/

void setup() {
  pinMode(BUZZER, OUTPUT);
  attachInterrupt( 0,playpause , FALLING);
}


/* La función loop reproduce la canción una y otra vez. */
void loop() {
  
  
       /* to calculate the note duration, take one second
       divided by the note type.
       e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.*/
      
 int noteDuration = 1000/tempo[thisNote];

        if(isplaying==1) 
{
          buzz(BUZZER, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(BUZZER, 0,noteDuration);
       thisNote++;
       if(thisNote == size)thisNote =0;
       }
}

/* Función que cambia de modo "play/pause" . Siendo 1 verdadero y 0 falso respectivamente. */

void playpause(){
  isplaying = 1 - isplaying;
}


void buzz(int targetPin, long frequency, long length) {
  
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    //analogWrite(targetPin,frecuencia);
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    //analogWrite(targetPin,frecuencia);
    //tone(targetPin, frecuencia, length);
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  
}


