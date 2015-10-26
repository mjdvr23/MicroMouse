


char  bt_val;

// ================================================================
// ===                        Motors                     ===
// ================================================================

const int in_1 = 3; // Left drive motor pin
const int in_2 = 5; // Left reverse motor pin
const int in_3 = 10;  // Rigth drive motor pin
const int in_4 = 9;  // Right reverse motor pin

int leftMotorPwm = 255;
int rightMotorPwm = 255;
int delayTime = 2000;


// ================================================================
// ===                        Right Encoder                     ===
// ================================================================

static const int encoder0RightPinA = 12;
static const int encoder0RightPinB = 13;
int encoder0RightPos = 0;
int encoder0RightPinALast = LOW;
int nRight = LOW;

// ================================================================
// ===                        Left Encoder                      ===
// ================================================================


static const  int encoder0LeftPinA = 2;
static const  int encoder0LeftPinB = 4;
int encoder0LeftPos = 0;
int encoder0LeftPinALast = LOW;
int nLeft = LOW;







// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  // put your setup code here, to run once:
  pinMode (in_1, OUTPUT);
  pinMode (in_2, OUTPUT);
  pinMode (in_3, OUTPUT);
  pinMode (in_4, OUTPUT);

  pinMode (encoder0RightPinA, INPUT);
  pinMode (encoder0RightPinB, INPUT);
  pinMode (encoder0LeftPinA, INPUT);
  pinMode (encoder0LeftPinB, INPUT);

  Serial.begin(9600);

}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    bt_val = Serial.read();
  }

  //Call Function for move the micromouse
  if (bt_val == 'u') {
    readLeftEncoder();
    drive(leftMotorPwm, rightMotorPwm);
    //  Serial.println("Driver function");

    delay(delayTime);
    bt_val = 'off';
  }

  if (bt_val == 'd') {
    reverse(leftMotorPwm, 255);
    Serial.println("Reverse function");
    delay(delayTime);
    bt_val = 'off';
  }

  if (bt_val == 'l') {
    left(leftMotorPwm);
    Serial.println("Left turn function");
    delay(delayTime); // angulo de giro , mas delay mas angulo de giro
    bt_val = 'off';
  }

  if (bt_val == 'r') {
    right(rightMotorPwm);
    Serial.println("Right turn function");
    delay(delayTime);
    bt_val = 'off';
  }

  if (bt_val == 's') {
    pausa();
    bt_val = 'off';
    Serial.println("Stop");
  }
  pausa();
  delay(100);

  //Loop finish


}


// ================================================================
// ===                        FUNCTIONS                         ===
// ================================================================

void drive(int valor1, int valor2) {

  if (valor1 > 255) {
    valor1 = 255;
  }

  if (valor2 > 255) {
    valor2 = 255;
  }

  analogWrite(in_1, valor1);
  analogWrite(in_2, 0);
  analogWrite(in_3, valor2);
  analogWrite(in_4, 0);
}


void reverse(int valor1, int valor2) {

  if (valor1 > 255) {
    valor1 = 255;
  }

  if (valor2 > 255) {
    valor2 = 255;
  }

  analogWrite(in_1, 0);
  analogWrite(in_2, valor1);
  analogWrite(in_3, 0);
  analogWrite(in_4, valor2);
}


void right(int valor) {

  if (valor  > 255) {
    valor = 255;
  }



  analogWrite(in_1, valor);
  analogWrite(in_2, 0);
  analogWrite(in_3, 0);
  analogWrite(in_4, 0);
}

void left(int valor) {

  if (valor  > 255) {
    valor = 255;
  }


  analogWrite(in_1, 0);
  analogWrite(in_2, 0);
  analogWrite(in_3, valor);
  analogWrite(in_4, 0);
}

void pausa() {

  analogWrite(in_1, 0);
  analogWrite(in_2, 0);
  analogWrite(in_3, 0);
  analogWrite(in_4, 0);
}

void readRightEncoder() {
  nRight = digitalRead(encoder0RightPinA);
  if ((encoder0RightPinALast == LOW) && (nRight == HIGH)) {
    if (digitalRead(encoder0RightPinB) == LOW) {
      encoder0RightPos--;
    } else {
      encoder0RightPos++;
    }
    Serial.println (" The Right encoder is : " + encoder0RightPos);
    Serial.println ("");
    delay(200);
  }
  encoder0RightPinALast = nRight;
}

void readLeftEncoder() {
  nLeft = digitalRead(encoder0LeftPinA);
  if ((encoder0LeftPinALast == LOW) && (nLeft == HIGH)) {
    if (digitalRead(encoder0LeftPinB) == LOW) {
      encoder0LeftPos--;
    } else {
      encoder0LeftPos++;
    }
    Serial.println (" The Left encoder is : " + encoder0LeftPos);
    Serial.println("");
    delay(200);

  }
  encoder0LeftPinALast = nLeft;
}



