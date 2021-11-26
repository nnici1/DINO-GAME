#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C Lcd(0x27, 16, 2);

int i;
int x;
int d;
int x1;
long timer_last;

int fLen = 5;
int mLen = 5;

int fx[5];
int mx[5];



void setup() {
  Lcd.init ();
  Lcd.backlight();
  pinMode(4, INPUT_PULLUP);
  x = 16;
  d = 400;
  for (int i = 0; i < fLen; i++) {
    mx[i] = -1;
    fx[i] = -1;
  }

  timer_last = 0;
  Lcd.setCursor(3, 0);
  Lcd.print("DINO  GAME");
  i = digitalRead (4);
  while (i == 1) {
    i = digitalRead (4);
  }
  Lcd.clear();
  delay(100);
  timer_last = millis();
}

void loop() {
  i = digitalRead (4);
  Lcd.clear();
  Lcd.setCursor(3, i);
  Lcd.print("o");
  for (int m = 0; m < fLen; m++) {
    if (fx[m] > -1)
      fx[m]--;
    else
      fx[m] = random(18, 41);
    Lcd.setCursor(fx[m], 1);
    Lcd.print("f");
  }

  for (int m = 0; m < mLen; m++) {
    if (mx[m] > -1)
      mx[m]--;
    else
      mx[m] = random(18, 41);
    Lcd.setCursor(mx[m], 0);
    Lcd.print("m");
  }

  kollision();
  for (int m = 0; m < mLen; m++) {
    for (int i = 0; i < mLen; i++)
      if (fx[i] == mx[m] )
        mx[m] = -1;
  }
  delay (d);
  Lcd.clear();
  i = digitalRead (4);
  Lcd.setCursor(3, i);
  Lcd.print("o");


  if (d > 200)
    d = d - 1;
}

void gameOver() {
  Lcd.clear();
  Lcd.setCursor(3, 0);
  Lcd.print("GAME  OVER");
  Lcd.setCursor(3, 1);
  Lcd.print("SCORE:");
  Lcd.setCursor(9, 1);
  Lcd.print((millis() - timer_last) / 1000);
  delay(2000);
}



void kollision() {
  for (int s = 0; s < fLen; s++) {
    if (i == 1 && fx[s] == 3) {
      gameOver();
      setup();
    }
  }
  for (int s = 0; s < mLen; s++) {
    if (i == 0 && mx[s] == 3) {
      gameOver();
      setup();
    }
  }
}
