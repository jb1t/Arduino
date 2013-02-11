#include "pitches.h"

int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);
const int buzzerPin = 8;
const int buttonPin = 12;

const int buzzerDuration = 500;
const int decrementDelay = 25;
const int minDelay = 25;
const int goalLEDIndex = 3;
const int maxMissedPresses = 3;
const unsigned int successTone = 2027;
const unsigned int failureTone = 1027;

int successMusicNote[] = {NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6}; //ccggaagffeeddc
int successMusicNoteDuration[] = {8,8,8,8,8,8,4,8,8,8,8,8,8,4};

String scoreMessage = "Your score is ";
String highScoreMessage = "High score is ";
String oopsMessage = "Oops number ";

//variables that change during game play
int score, countOfMissedPresses, currentLEDIndex, ledDelay, highScore = 0;

void setup() {               
 Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  for(int i=0; i < numberOfPins; i++)
  {
   pinMode(ledPins[i], OUTPUT); 
  }
  ResetGame();
}

void loop() { 
 
  if(IsButtonPressed())
  {
    if(currentLEDIndex == goalLEDIndex)
    {
      tone(buzzerPin,successTone,buzzerDuration);
      score++;
      ledDelay -= decrementDelay;
      if(ledDelay < minDelay)
        ledDelay = minDelay;
    }
    else
    {
      tone(buzzerPin,failureTone,buzzerDuration);
      countOfMissedPresses++;
      if(countOfMissedPresses >= maxMissedPresses)
      {
       Serial.println(scoreMessage + score);
       ResetGame(); 
       DisplayHighScore();
      }
      else
      {
       Serial.println(oopsMessage + countOfMissedPresses); 
      }
    }
    BlinkLED(currentLEDIndex, 200);
    BlinkLED(currentLEDIndex, 200);  
  }
  BlinkLED(currentLEDIndex, ledDelay);
  IncrementLEDIndex();  
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

void DisplayHighScore()
{
   Serial.println(highScoreMessage + highScore); 
}

void ResetGame()
{
 if(score > highScore)
 {
   playSuccessMusic();
   highScore = score;
 }
 currentLEDIndex = 0;
 ledDelay = 250;
 score = 0;
 countOfMissedPresses = 0;
}

void IncrementLEDIndex()
{
  currentLEDIndex = (currentLEDIndex + 1)%(numberOfPins);
}

boolean IsButtonPressed()
{ 
  if(digitalRead(buttonPin) == 0)
  {
    return true;
  }
  else
  {
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
