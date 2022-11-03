#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo lockingLug;
String code = "";

int buttonsPressed = -1;

bool easyBeaten = false;
bool mediumBeaten = false;
bool hardBeaten = false;

int easyCodeSequence[4] = { 3, 1, 4, 2 };
int mediumCodeSequence[4] = { 8, 7, 6, 5 };
int hardCodeSequence[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };

int currentSequence[8];

bool correctFlash[8] = { false, false, false, false, false, false, false, false };
int ledIndex = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);  //green LED
  pinMode(9, OUTPUT);  //red LED
  lockingLug.attach(13);
  lockingLug.write(90);  //locks the lock
  Serial.begin(9600);
}
/*
CODE CYPHER
1 = W
2 = A
3 = S
4 = D
5 = UP
6 = DOWN
7 = RIGHT
8 = LEFT
*/
void loop() {
  lcd.setCursor(0, 0);
  lcd.print(displayArray());
  if (!easyBeaten) {
    if (currentSequence[buttonsPressed] == easyCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      if (ledIndex == buttonsPressed && correctFlash[ledIndex] == false) {
        correctNumber();
      }

      if (buttonsPressed >= 3 && currentSequence[3] == easyCodeSequence[3]) {
        Serial.println("Correct Code! Tutorial 1 Done!");
        digitalWrite(8, HIGH);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("CORRECT!");

        delay(5000);  //wait x amount of seconds to relock the lock

        reset();

        easyBeaten = true;
      }
    } else if (currentSequence[buttonsPressed] != easyCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      Serial.println("Incorrect Code");
      reset();
      wrongOrder();
    }
  }

  else if (!mediumBeaten) {
    if (currentSequence[buttonsPressed] == mediumCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      if (ledIndex == buttonsPressed && correctFlash[ledIndex] == false) {
        correctNumber();
      }

      if (buttonsPressed >= 3 && currentSequence[3] == mediumCodeSequence[3]) {
        Serial.println("Correct Code! Tutorial 2 Done!");
        digitalWrite(8, HIGH);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("CORRECT!");

        delay(5000);  //wait x amount of seconds to relock the lock

        reset();

        mediumBeaten = true;
      }
    } else if (currentSequence[buttonsPressed] != mediumCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      Serial.println("Incorrect Code");
      reset();
      wrongOrder();
    }

  } else if (!hardBeaten) {
    if (currentSequence[buttonsPressed] == hardCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      if (ledIndex == buttonsPressed && correctFlash[ledIndex] == false) {
        correctNumber();
      }

      if (buttonsPressed >= 7 && currentSequence[7] == hardCodeSequence[7]) {
        Serial.println("Correct Code! LockPickingLawyer would be proud!!");
        lockingLug.write(0);  //unlocks lock
        digitalWrite(8, HIGH);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("CANDY TIME");
        delay(5000);  //wait x amount of seconds to relock the lock

        reset();
      }
    } else if (currentSequence[buttonsPressed] != hardCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      Serial.println("Incorrect Code");
      reset();
      wrongOrder();
    }
  }

  // Send some message when I receive 1-8 from the row of numbers
  switch (Serial.read()) {
    case '1':
      assignValueToSequence(1);
      debug(9, 1);
      break;

    case '2':
      assignValueToSequence(2);
      debug(8, 2);
      break;

    case '3':
      assignValueToSequence(3);
      debug(7, 3);
      break;

    case '4':
      assignValueToSequence(4);
      debug(6, 4);
      break;

    case '5':
      assignValueToSequence(5);
      debug(5, 5);
      break;

    case '6':
      assignValueToSequence(6);
      debug(4, 6);
      break;

    case '7':
      assignValueToSequence(7);
      debug(3, 7);
      break;

    case '8':
      assignValueToSequence(8);
      debug(2, 8);
      break;
  }
}
void correctNumber() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(smarty());
  digitalWrite(8, HIGH);
  delay(200);
  digitalWrite(8, LOW);
  correctFlash[ledIndex] = true;
  ledIndex++;
}

String smarty() {
  int rand = random(5);
  String string = "";

  switch (rand) {
    case 0:
      string = "Nice!";
      break;

    case 1:
      string = "Keep Going!";
      break;

    case 2:
      string = "A Natural!";
      break;

    case 3:
      string = "Superb!";
      break;

    case 4:
      string = "Don't Stop!";
      break;
  }

  return string;
}

String dummy() {
  int rand = random(5);
  String string = "";

  switch (rand) {
    case 0:
      string = "Wrong!";
      break;

    case 1:
      string = "Crap!";
      break;

    case 2:
      string = "Skill Issue!";
      break;

    case 3:
      string = "Dogwater!";
      break;

    case 4:
      string = "Nope!";
      break;
  }

  return string;
}

void debug(int pin, int num) {
  //digitalWrite(pin, HIGH);
  Serial.print("Code: ");
  Serial.print(code);
  Serial.print(" - ");
  Serial.println(num);
}

void reset() {
  buttonsPressed = -1;
  code = "";
  memset(currentSequence, 0, sizeof(currentSequence));
  lockingLug.write(90);
  digitalWrite(8, LOW);

  lcd.clear();

  ledIndex = 0;
  for (int i = 0; i < 8; i++) {
    correctFlash[i] = false;
  }
}

void wrongOrder() {
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);

  lcd.setCursor(0, 1);
  lcd.print(dummy());

  delay(300);
  digitalWrite(9, LOW);
}

void assignValueToSequence(int num) {
  code += num;
  for (int i = 0; i < 8; i++) {
    if (currentSequence[i] == 0) {
      currentSequence[i] = num;
      break;
    }
  }

  buttonsPressed++;
}

String displayArray() {
  String code = "";
  for (int i = 0; i < 8; i++) {
    if (currentSequence[i] != 0) {
      code += currentSequence[i];
    }

    else {
      break;
    }
  }

  return code;
}