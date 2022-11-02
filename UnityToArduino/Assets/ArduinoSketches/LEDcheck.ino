#include <Servo.h>
String code = "";
int buttonsPressed = 0;
Servo lockingLug;

void setup()
{
    lockingLug.attach(9);
    lockingLug.write(90); //locks the lock
    Serial.begin(9600);
    
}

void loop()
{
  //checks if code is correct
    if(code.toInt() == 87654321) {
      Serial.println("Correct Code!");
      lockingLug.write(0); //unlocks lock
      delay(2000); //wait x amount of seconds to relock the lock
      lockingLug.write(90); //relocks the lock 
      code = ""; //resets the code sequence
      buttonsPressed = 0; //resets the number of buttons pressed
    
    }

    if(buttonsPressed >= 8 && code.toInt() != 87654321) {
      buttonsPressed = 0;
      code = "";
      lockingLug.write(90);
      Serial.println("Incorrect Code");
    }

    // Send some message when I receive 1-8 from the row of numbers
    switch (Serial.read())
    {
        case '1':
            code += 1;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("1");
            break;
        case '2':
            code += 2;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("2");
            break;
        case '3':
            code += 3;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("3");
            break;
        case '4':
            code += 4;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("4");
            break;
        case '5':
            code += 5;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("5");
            break;
        case '6':
            code += 6;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("6");
            break;
        case '7':
            code += 7;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("7");
            break;
        case '8':
            code += 8;
            buttonsPressed++;
            Serial.print(code);
            Serial.print(" - ");
            Serial.println("8");
            break;
    }
}