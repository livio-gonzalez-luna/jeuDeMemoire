#include <LiquidCrystal.h>

int ledPins[] = {A5, A4, A3, A2};
int buttonPins[] = {2, 3, 4, 5};
int buttonStates[] = {LOW, LOW, LOW, LOW};
int lastButtonStates[] = {LOW, LOW, LOW, LOW};
int sequence[100];
int sequenceLength = 2;
int score = 0;

LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  lcd.begin(16, 2);
  lcd.print("Score: 0");
}

void loop()
{
  if (sequenceLength == 2) {  
    for (int i = 0; i < sequenceLength; i++)
    {
      generatenum(i);
    }
  }
  for (int i = 0; i < sequenceLength; i++)
  {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(250);
  }
  for (int i = 0; i < sequenceLength; i++)
  {
    int buttonPressed = -1;
    while (buttonPressed == -1)
    {
      for (int j = 0; j < 4; j++)
      {
        buttonStates[j] = digitalRead(buttonPins[j]);
        if (buttonStates[j] != lastButtonStates[j])
        {
          if (buttonStates[j] == LOW)
          {
            buttonPressed = j;
            digitalWrite(ledPins[j], HIGH); 
          }
          lastButtonStates[j] = buttonStates[j];
        }
      }
    }
    delay(200);
    digitalWrite(ledPins[buttonPressed], LOW);

    if (buttonPressed != sequence[i])
    {
      lcd.clear();
      lcd.print("Score: ");
      lcd.print(score);
      lcd.setCursor(0, 1);
      lcd.print("Game over!");
      delay(2000);
      sequenceLength = 2;
      score = 0;
      lcd.clear();
      lcd.print("Score: 0");
      return;
    }
  }
  delay(300);
  
  score++;
  sequenceLength++;
  generatenum(sequenceLength);
  lcd.clear();
  lcd.print("Score: ");
  lcd.print(score);
}


void generatenum(int num)
{
  int randomnum = random(0, 4);
  sequence[num] = randomnum;
}