/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledPins[] = {2,3,4,5};
int numberOfPins = 4;

int on_delay = 1000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(int i=0; i < numberOfPins; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
}

// the loop routine runs over and over again forever:
void loop() {
  
  for(int i=0; i<10; i++)
  {  
    displayNumber(i);
    resetPins();
  }  
}

void displayNumber(int number)
{
  int tmpNumber = number;  
    for(int j=0; j<numberOfPins; j++)
    {
      if((tmpNumber&1) == 1)
      {
        digitalWrite(ledPins[j], HIGH); 
      }
      tmpNumber = tmpNumber >> 1;
    }
    delay(on_delay);
}

void resetPins() {
 
 for(int i=0; i<numberOfPins; i++)
 {
   digitalWrite(ledPins[i], LOW);
 } 
}

