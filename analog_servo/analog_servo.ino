#include <Servo.h> 

Servo myservo;

const int servoPin = A0;
const int minAngle = 0;
const int maxAngle = 90;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(servoPin);//, minAngle, maxAngle);
} 

void loop() 
{
  int oldAngle = 0;
  int newAngle = 0;
  while(Serial.available() > 0)
  {
    while(newAngle >= 0 && newAngle <= 180)
    {
      newAngle = Serial.parseInt();
      Serial.print("Angle writing ");
      Serial.println(newAngle);
      myservo.write(newAngle);
      delay(calculateDelay(oldAngle, newAngle));
      oldAngle = newAngle;
      if(Serial.peek() == '\n')
      {
        newAngle = -1;
        Serial.read();
      }  
    }
  }  
} 

int calculateDelay(int oldAngle, int newAngle)
{
  //for every degree it takes 2 milliseconds for this servo to move
  return abs(oldAngle-newAngle)*2;
}
