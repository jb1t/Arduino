int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);

int on_delay = 500;

void setup() {                
  for(int i=0; i < numberOfPins; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() {
  
  for(int i=0; i<10; i++)
  {  
    displayNumber(i);
    resetPins();
  }  
}

void displayNumber(int number)
{
    for(int j=0; j<numberOfPins; j++)
    {
      if(bitRead(number, j) == 1)
      {
        digitalWrite(ledPins[j], HIGH); 
      }
    }
    delay(on_delay);
}

void resetPins() {
 for(int i=0; i<numberOfPins; i++)
 {
   digitalWrite(ledPins[i], LOW);
 } 
}

