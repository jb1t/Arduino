int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);
int sensorPin = A0; // analog input pin
int on_delay = 500;

void setup() {                
  Serial.begin(9600); // used for output
  for(int i=0; i < numberOfPins; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() {
  for(int i=0; i<pow(2,numberOfPins+1); i++)
  {  
    int sensorValue = getSensorValue();
    displayNumber(i);
    delay(map(sensorValue, 0, 1023, 10, 1000));

    //Serial.print("The sensorValue is ");
    //Serial.println(sensorValue);

    resetPins();
  }  
}

int getSensorValue()
{
  int sensorValue = analogRead(sensorPin);
  //sensorVoltage = sensorValue*(5.0/1023.0);
  return sensorValue;  
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
}

void resetPins() {
 for(int i=0; i<numberOfPins; i++)
 {
   digitalWrite(ledPins[i], LOW);
 } 
}

