int ledPins[] = {2,3,4,5};
int numberOfPins = sizeof(ledPins)/sizeof(int);

const int decrementDelay = 25;
const int minDelay = 25;
const int buttonPin = 12;
const int goalLEDIndex = 3;
const int maxMissedPresses = 3;
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
      score++;
      ledDelay -= decrementDelay;
      if(ledDelay < minDelay)
        ledDelay = minDelay;
    }
    else
    {
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

void DisplayHighScore()
{
   Serial.println(highScoreMessage + highScore); 
}

void ResetGame()
{
 if(score > highScore)
   highScore = score;
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
