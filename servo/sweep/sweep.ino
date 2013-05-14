#include <Servo.h> 
#include "pitches.h"

Servo myservo;  
const int buttonPin = 4;
const int ledPin = 2;
const int buzzerPin = 3;
const int servoPin = 9;

unsigned long lastExecution = 4500000; // 1.25hrs 

int maxRotationSpeedClockwise = 0;
int stopRotation = 90;
unsigned long rotationDelayMilliseconds = 1500; // 2000 milliseconds (i.e. 2 seconds)
unsigned long pauseInterval = 43200000;// (i.e. 12 hours)
unsigned long ledFlashDelay = 100;
unsigned long loopDelay = 10;
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
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
    unsigned long timeLeft = lastExecution + pauseInterval - millis();
    Serial.print("timeLeft=");
    Serial.println(timeLeft);
   delay(loopDelay); 
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
  LedFlash(20);
  playAlarmMusic();
}

void LedFlash(int numberOfFlashes)
{
  for(int i=0; i<numberOfFlashes; ++i)
  {
    digitalWrite(ledPin, HIGH);
    delay(ledFlashDelay);
    digitalWrite(ledPin, LOW);
    delay(ledFlashDelay); 
  }
}

boolean IsButtonPressed()
{ 
  if(digitalRead(buttonPin) == 0)
  {
    //Serial.println("IsButtonPressed() = true");
    return true;
  }
  else
  {
    //Serial.println("IsButtonPressed() = false");
    return false;
  }
}

int alarmNotes[] = {NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6}; //ccggaagffeeddc
int alarmNotesDuration[] = {8,8,8,8,8,8,4,8,8,8,8,8,8,4};

void playAlarmMusic()
{
 for (int thisNote = 0; thisNote < (sizeof(alarmNotes)/sizeof(int))-1; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/alarmNotesDuration[thisNote];
    tone(buzzerPin, alarmNotes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
  } 
}
