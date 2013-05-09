// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
                
const int buttonPin = 12;

int maxRotationSpeedClockwise = 0;
int stopRotation = 90;
long rotationDelayMilliseconds = 2000; // 2000 milliseconds (i.e. 2 seconds)
long stopRotationDelayMilliseconds = 60000; // 1000 * 60 * 60 * 12; //43200000 (i.e. 12 hours)
 
void setup() 
{ 
  //Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(stopRotation);
} 
 
 
void loop() 
{ 
  if(IsButtonPressed())
  {
    RotateServosAndThenStop();
    //delay(stopRotationDelayMilliseconds);
  }
  else
  {
   delay(10); 
  }
}

void RotateServosAndThenStop()
{
  myservo.write(maxRotationSpeedClockwise);
  delay(rotationDelayMilliseconds);
  myservo.write(stopRotation);
}

boolean IsButtonPressed()
{ 
  if(digitalRead(buttonPin) == 0)
  {
    //Serial.println("true");
    return true;
  }
  else
  {
    //Serial.println("false");
    return false;
  }
}
