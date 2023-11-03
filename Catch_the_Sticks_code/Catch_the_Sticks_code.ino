#define CLK 6
#define DIO 5
#define stButton 3
#define menButton 4

#include <GyverTM1637.h>
GyverTM1637 disp(CLK, DIO);

int level = 1; // вибір рівня складності від 1 до 4

const int ARRAY_SIZE = 10;
int magnetPins[] = {7, 8, 9, 10, 11, 12, 13, A0, A1, A2}; // масив з пінами 10 магнітів
int lagDelays[] = {700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150};

bool mainflag = 0;
bool stflag = 0;
bool menflag = 0;

byte stButt = 0;
byte menButt = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A3));

  pinMode(stButton, INPUT_PULLUP);
  pinMode(menButton, INPUT_PULLUP);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    pinMode(magnetPins[i], OUTPUT);
  }

  disp.clear();
  disp.brightness(7);
  magnetize();
}

void loop() {
  stButt = digitalRead(stButton);
  menButt = digitalRead(menButton);

  if (stButt && stflag) {
    mainflag = 1;
    stflag = 0;
  } else if (!stButt && !stflag) {
    stflag = 1;
  }

  if (menButt && menflag) {
    level++;
    menflag = 0;
  } else if (!menButt && !menflag) {
    delay(100);
    menflag = 1;
  }
  if (level > 4) level = 1;
  disp.display(0, level);

  if (mainflag) {
    disp.displayByte(1, _S);
    disp.displayByte(2, _t);
    delay(5000);
    for (int i = 0; i < ARRAY_SIZE; i++) { //перемішуємо піни
      int j = random(i, ARRAY_SIZE);
      int temp = magnetPins[i];
      magnetPins[i] = magnetPins[j];
      magnetPins[j] = temp;
    }
    if (level == 1) {
      for (int i = 0; i < ARRAY_SIZE; i++) {
        counter(i);
        digitalWrite(magnetPins[i], LOW);
        delay(1700);
        Serial.println(magnetPins[i]);
      }
    }

    else if (level == 2) {
      for (int i = 0; i < ARRAY_SIZE; i++) {
        counter(i);
        digitalWrite(magnetPins[i], LOW);
        delay(1300);
        Serial.println(magnetPins[i]);
      }
    }

    else if (level == 3) {
      for (int i = 0; i < ARRAY_SIZE; i++) { //перемішуємо час
        int j = random(i, ARRAY_SIZE);
        int temp2 = lagDelays[i];
        lagDelays[i] = lagDelays[j];
        lagDelays[j] = temp2;
      }
      for (int i = 0; i < ARRAY_SIZE; i++) {
        counter(i);
        digitalWrite(magnetPins[i], LOW);
        delay(lagDelays[i] + 200);
        Serial.print(magnetPins[i]);
        Serial.print("\t");
        Serial.println(lagDelays[i]);
      }
    }

    else if (level == 4) {
      for (int i = 0; i < ARRAY_SIZE; i++) { //перемішуємо час
        int j = random(i, ARRAY_SIZE);
        int temp2 = lagDelays[i];
        lagDelays[i] = lagDelays[j];
        lagDelays[j] = temp2;
      }
      for (int i = 0; i < ARRAY_SIZE; i++) {
        counter(i);
        digitalWrite(magnetPins[i], LOW);
        delay(lagDelays[i]);
        Serial.print(magnetPins[i]);
        Serial.print("\t");
        Serial.println(lagDelays[i]);
      }
    }
    mainflag = 0;
    magnetize();
    disp.displayByte(1, _empty);
    disp.displayByte(2, _empty);
    disp.displayByte(3, _empty);
  }
}

void magnetize() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    digitalWrite(magnetPins[i], HIGH);
  }
}

void counter(int x) {
  if (x == 0) disp.display(3, 0);
  else disp.display(3, 10 - x);
}
