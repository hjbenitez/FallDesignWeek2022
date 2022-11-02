#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
String code = "";
int buttonsPressed = -1;

bool easyBeaten = false;
bool mediumBeaten = false;
bool hardBeaten = false;

int easyCodeSequence[4] = { 4, 3, 2, 1 };

int mediumCodeSequence[4] = { 8, 7, 6, 5 };

int hardCodeSequence[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };

int currentSequence[8];
Servo lockingLug;

void setup() {
  lcd.begin(16, 2);

  
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
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
  lcd.print("bitch");
  if (!easyBeaten) {
    if (currentSequence[buttonsPressed] == easyCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      digitalWrite(2, HIGH);

      if (buttonsPressed >= 3 && currentSequence[3] == easyCodeSequence[3]) {
        Serial.println("Correct Code! Tutorial  Done!");
        delay(5000);  //wait x amount of seconds to relock the lock

        code = "";
        lockingLug.write(90);                                 //relocks the lock
        memset(currentSequence, 0, sizeof(currentSequence));  //resets the code sequence
        buttonsPressed = -1;                                  //resets the number of buttons pressed

        //Reset LEDs

        digitalWrite(3, LOW);
        digitalWrite(2, LOW);

        easyBeaten = true;
      }
    } else if (currentSequence[buttonsPressed] != easyCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      buttonsPressed = -1;
      code = "";
      memset(currentSequence, 0, sizeof(currentSequence));
      lockingLug.write(90);
      Serial.println("Incorrect Code");

      digitalWrite(3, HIGH);
      delay(400);
      //reset LEDs
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    }

  }

  else if (!mediumBeaten) {
    if (currentSequence[buttonsPressed] == mediumCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      digitalWrite(buttonsPressed + 2, HIGH);

      if (buttonsPressed >= 3 && currentSequence[3] == mediumCodeSequence[3]) {
        Serial.println("Correct Code! Tutorial 2 Done!");
        delay(5000);  //wait x amount of seconds to relock the lock

        code = "";
        lockingLug.write(90);                                 //relocks the lock
        memset(currentSequence, 0, sizeof(currentSequence));  //resets the code sequence
        buttonsPressed = -1;                                  //resets the number of buttons pressed

        //Reset LEDs
        
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);

        mediumBeaten = true;
      }
    } else if (currentSequence[buttonsPressed] != mediumCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      buttonsPressed = -1;
      code = "";
      memset(currentSequence, 0, sizeof(currentSequence));
      lockingLug.write(90);
      Serial.println("Incorrect Code");

      //reset LEDs
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    }

  } else if (!hardBeaten) {
    if (currentSequence[buttonsPressed] == hardCodeSequence[buttonsPressed] && currentSequence[buttonsPressed] != 0) {
      digitalWrite(buttonsPressed + 2, HIGH);

      if (buttonsPressed >= 7 && currentSequence[7] == hardCodeSequence[7]) {
        Serial.println("Correct Code! LockPickingLawyer would be proud!!");
        lockingLug.write(0);  //unlocks lock
        delay(5000);          //wait x amount of seconds to relock the lock

        lockingLug.write(90);                                 //relocks the lock
        memset(currentSequence, 0, sizeof(currentSequence));  //resets the code sequence
        buttonsPressed = -1;                                  //resets the number of buttons pressed

        //Reset LEDs
        
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
      }
    }

    else if (currentSequence[buttonsPressed] != hardCodeSequence[buttonsPressed] && buttonsPressed != -1) {
      buttonsPressed = -1;
      code = "";
      memset(currentSequence, 0, sizeof(currentSequence));
      lockingLug.write(90);
      Serial.println("Incorrect Code");

      //reset LEDs
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    }
  }


  // Send some message when I receive 1-8 from the row of numbers
  switch (Serial.read()) {
    case '1':
      assignValueToSequence(1);
      buttonsPressed++;
      debug(9, 1);
      break;

    case '2':
      assignValueToSequence(2);
      buttonsPressed++;
      debug(8, 2);
      break;

    case '3':
      assignValueToSequence(3);
      buttonsPressed++;
      debug(7, 3);
      break;

    case '4':
      assignValueToSequence(4);
      buttonsPressed++;
      debug(6, 4);
      break;

    case '5':
      assignValueToSequence(5);
      buttonsPressed++;
      debug(5, 5);
      break;

    case '6':
      assignValueToSequence(6);
      buttonsPressed++;
      debug(4, 6);
      break;

    case '7':
      assignValueToSequence(7);
      buttonsPressed++;
      debug(3, 7);
      break;

    case '8':
      assignValueToSequence(8);
      buttonsPressed++;
      debug(2, 8);
      break;

    case '0':
      checkArray();
      Serial.println(" Current Sequence");
      break;
  }
}

void debug(int pin, int num) {
  //digitalWrite(pin, HIGH);
  Serial.print("Code: ");
  Serial.print(code);
  Serial.print(" - ");
  Serial.println(num);
}

void assignValueToSequence(int num) {
  code += num;
  for (int i = 0; i < 8; i++) {
    if (currentSequence[i] == 0) {
      currentSequence[i] = num;
      break;
    }
  }
}

void checkArray() {
  for (int i = 0; i < 8; i++) {
    Serial.print(currentSequence[i]);
  }
}