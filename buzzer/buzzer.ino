/*pi
Simple Scale Sweep
*/
#include "pitches.h"

int buzzerPin = 8;
int currentNote = 0;
unsigned int note[] = {1047,1175,1319,1397,1568,1760,1976,2093};
int maxNumberOfNotes = sizeof(note)/sizeof(unsigned int);
// the setup routine runs once when you press reset:
void setup() {    
  Serial.begin(9600);  
  // nothing to setup
  Serial.println(maxNumberOfNotes);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(currentNote);
  Serial.println(note[currentNote]);
  tone(buzzerPin, note[currentNote++], 500);  
  delay(500);
  currentNote = currentNote % maxNumberOfNotes;
}

