int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);
int ledDelay = 250;
const int decrementDelay = 2;
int minDelay = 25;

int buttonPin = 12;
int currentLEDIndex = 0;
int goalLEDIndex = 3;

void setup() {               
 Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  for(int i=0; i < numberOfPins; i++)
  {
   pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() { 
 
  if(IsButtonPressed())
  {
    if(currentLEDIndex == goalLEDIndex)
    {
      Serial.println("Button pressed on the GOAL button!");
      ledDelay -= decrementDelay;
      if(ledDelay < minDelay)
        ledDelay = minDelay;
    }
    BlinkLED(currentLEDIndex, 200);
    BlinkLED(currentLEDIndex, 200);  
  }
  BlinkLED(currentLEDIndex, ledDelay);
  IncrementLEDIndex();
  
}

void IncrementLEDIndex()
{
  currentLEDIndex = (currentLEDIndex + 1)%(numberOfPins);
}

boolean IsButtonPressed()
{ 
  if(digitalRead(buttonPin) == 0)
  {
    Serial.println("Button pressed!");
    return true;
  }
  else
  {
    Serial.println("Button NOT pressed");
    return false;
  }
}

void BlinkLED(int ledIndex, int duration)
{
  digitalWrite(ledPins[ledIndex], HIGH); 
  delay(duration);
  digitalWrite(ledPins[ledIndex], LOW); 
  delay(duration);
}
