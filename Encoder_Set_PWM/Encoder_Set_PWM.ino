
const int in_1 = 3; // Left drive motor pin
const int in_2 = 5; // Left reverse motor pin
const int in_3 = 10;  // Rigth drive motor pin
const int in_4 = 9;  // Right reverse motor pin

int valLeft;
int encoder0PinALeft = 12;
int encoder0PinBLeft = 13;
int encoder0PosLeft = 0;
int encoder0PinALastLeft = LOW;
int nLeft = LOW;
int prevPosLeft;

int valRight;
int encoder0PinARight = 2;
int encoder0PinBRight = 4;
int encoder0PosRight = 0;
int encoder0PinALastRight = LOW;
int nRight = LOW;
int prevPosRight;


int pwmLeft = 0;
int pwmRight = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode (in_1, OUTPUT);
  pinMode (in_2, OUTPUT);
  pinMode (in_3, OUTPUT);
  pinMode (in_4, OUTPUT);




  pinMode (encoder0PinALeft, INPUT);
  pinMode (encoder0PinBLeft, INPUT);
  pinMode (encoder0PinARight, INPUT);
  pinMode (encoder0PinBRight, INPUT);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkRightEncoder();
  setPWMRight();



}


void setPWMRight() {

  while (encoder0PosRight == 0) {
    encoder();
    pwmRight += 1;
    //Safe Mode
    if (pwmRight > 255) {
      pwmRight = 255;
    }


    analogWrite(in_3, pwmRight);
    if (encoder0PosRight > 0) {
      Serial.print("PWM Derecho ");
      Serial.println(pwmRight);
      pausaMotorRight();
    }
    delay(1000);
  }


}

void setPWMLeft() {

  while (encoder0PosLeft == 0) {
    encoder();
    pwmLeft += 1;
    if (pwmLeft > 255) {
      pwmLeft = 255;
    }
    analogWrite(in_1, pwmLeft);
    if (encoder0PosLeft > 0) {
      Serial.print("PWM Izquierdo ");
      Serial.println(pwmLeft);
      pausaMotorLeft();
    }
    delay(1000);
  }


}



void encoder() {


  nLeft = digitalRead(encoder0PinALeft);
  if ((encoder0PinALastLeft == LOW) && (nLeft == HIGH)) {
    if (digitalRead(encoder0PinBLeft) == LOW) {
      encoder0PosLeft--;
    } else {
      encoder0PosLeft++;
    }
    Serial.print ("Encoder left: ");
    Serial.print(encoder0PosLeft);
    Serial.print("   ");
    Serial.print ("Encoder Right: ");
    Serial.println(encoder0PosRight);


  }
  encoder0PinALastLeft = nLeft;

  nRight = digitalRead(encoder0PinARight);
  if ((encoder0PinALastRight == LOW) && (nRight == HIGH)) {
    if (digitalRead(encoder0PinBRight) == LOW) {
      encoder0PosRight--;
    } else {
      encoder0PosRight++;
    }

    Serial.print ("Encoder left: ");
    Serial.print(encoder0PosLeft);
    Serial.print("   ");
    Serial.print ("Encoder Right: ");
    Serial.println(encoder0PosRight);

  }

  encoder0PinALastRight = nRight;

}

void checkLeftEncoder() {
  nLeft = digitalRead(encoder0PinALeft);
  if ((encoder0PinALastLeft == LOW) && (nLeft == HIGH)) {
    if (digitalRead(encoder0PinBLeft) == LOW) {
      encoder0PosLeft--;
    } else {
      encoder0PosLeft++;
    }
    Serial.print ("Encoder left: ");
    Serial.print(encoder0PosLeft);
    Serial.print("   ");
    Serial.print ("Encoder Right: ");
    Serial.println(encoder0PosRight);


  }
  encoder0PinALastLeft = nLeft;

}

void checkRightEncoder() {
  nRight = digitalRead(encoder0PinARight);
  if ((encoder0PinALastRight == LOW) && (nRight == HIGH)) {
    if (digitalRead(encoder0PinBRight) == LOW) {
      encoder0PosRight--;
    } else {
      encoder0PosRight++;
    }

    Serial.print ("Encoder left: ");
    Serial.print(encoder0PosLeft);
    Serial.print("   ");
    Serial.print ("Encoder Right: ");
    Serial.println(encoder0PosRight);

  }

  encoder0PinALastRight = nRight;
}

void pausaMotorRight() {
  analogWrite(in_3, 0);
}

void pausaMotorLeft() {
  analogWrite(in_1, 0);
}






