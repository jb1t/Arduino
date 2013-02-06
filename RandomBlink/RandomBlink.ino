/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledPins[] = {2,3,4,5,6};
int numberOfPins = 5;
int randomIndex = 0;
int on_delay = 1000;
int off_delay = 200;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(int i=0; i < numberOfPins; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
  randomSeed(analogRead(0)); 
}

// the loop routine runs over and over again forever:
void loop() {
  
  randomIndex = (int)random(0,numberOfPins);
  digitalWrite(ledPins[randomIndex], HIGH);
  delay(on_delay);
  digitalWrite(ledPins[randomIndex], LOW);
  delay(off_delay);
  
}

