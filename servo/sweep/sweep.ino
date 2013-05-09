// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#include "pitches.h"

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
                
const int buttonPin = 12;
const int ledPin = 7;
const int buzzerPin = 8;

unsigned long lastExecution;

int maxRotationSpeedClockwise = 0;
int stopRotation = 90;
long rotationDelayMilliseconds = 2000; // 2000 milliseconds (i.e. 2 seconds)
unsigned long pauseInterval = 43200000;// (i.e. 12 hours)

const unsigned int successTone = 2027;
const unsigned int failureTone = 1027;
int successMusicNote[] = {NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6}; //ccggaagffeeddc
int successMusicNoteDuration[] = {8,8,8,8,8,8,4,8,8,8,8,8,8,4};
 
void setup() 
{ 
  //Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(stopRotation);
} 
 
 
void loop() 
{ 
  if(IsButtonPressed() || (lastExecution + pauseInterval) < millis())
  {
    lastExecution = millis();
    RaiseAlarm();
    RotateServosAndThenStop();    
  }
  else
  {
   delay(10); 
  }
}

void RotateServosAndThenStop()
{
  digitalWrite(ledPin, HIGH);
  myservo.write(maxRotationSpeedClockwise);
  delay(rotationDelayMilliseconds);
  myservo.write(stopRotation);
  digitalWrite(ledPin, LOW);
}

void RaiseAlarm()
{
  playSuccessMusic();
  for(int i=0; i<10; ++i)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
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

void playSuccessMusic()
{
 for (int thisNote = 0; thisNote < 14; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/successMusicNoteDuration[thisNote];
    tone(buzzerPin, successMusicNote[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
  } 
}
