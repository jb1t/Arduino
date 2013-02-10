int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);
int maxNumber = 1<<numberOfPins;
int sensorPin = A0; // analog input pin
int on_delay = 500;
int currentNumber = 0;

void setup() {                
  Serial.begin(9600); // used for output
  for(int i=0; i < numberOfPins; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() { 
    
  int sensorValue = GetSensorValue();
  DisplayNumber(currentNumber);
  delay(map(sensorValue, 0, 1023, 10, 1000)); //min delay is 10 milliseconds and max is 1 second

  ResetPins();  
  SetCurrentNumber();  
}

void SetCurrentNumber()
{
  if(++currentNumber >= maxNumber)
    currentNumber = 0;
}

int GetSensorValue()
{
  int sensorValue = analogRead(sensorPin);
  //sensorVoltage = sensorValue*(5.0/1023.0);
  Serial.print("The sensorValue is ");
  Serial.println(sensorValue);
  return sensorValue;  
}

void DisplayNumber(int number)
{
  for(int j=0; j<numberOfPins; j++)
  {
    if(bitRead(number, j) == 1)
    {
      digitalWrite(ledPins[j], HIGH); 
    }
  }
}

void ResetPins() {
 for(int i=0; i<numberOfPins; i++)
 {
   digitalWrite(ledPins[i], LOW);
 } 
}

