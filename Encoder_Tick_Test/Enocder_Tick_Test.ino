
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

int valRight;
int encoder0PinARight = 2;
int encoder0PinBRight = 4;
int encoder0PosRight = 0;
int encoder0PinALastRight = LOW;
int nRight = LOW;
int empieza = 0;


int pwm = 250;


unsigned long startTime;
unsigned long endTime;
unsigned long timeRun = 5000;


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

  if (empieza == 0) {
    analogWrite(in_1, pwm);
    analogWrite(in_3, pwm);
    startTime = millis();
    empieza = 1;
  }
  endTime = millis();

  if ((endTime - startTime) <= timeRun) {
    encoders();
    checkEncoders();
  }
  else
    pausaMotor(true, true);
}


void forward(boolean runMotor1, boolean runMotor2) {
  if (runMotor1)
    analogWrite(in_3, pwm);
  else
    analogWrite(in_3, 0);
  if (runMotor2)
    analogWrite(in_1, pwm);
  else
    analogWrite(in_1, 0);




}

void checkEncoders() {
  if (encoder0PosRight > encoder0PosLeft) {
    forward(false, true);

  }
  else if (encoder0PosRight < encoder0PosLeft) {
    forward(true, false);
  }
  else
    forward(true, true);

}

void pausaMotor(boolean stopMotor1, boolean stopMotor2) {
  if (stopMotor1)
    analogWrite(in_1, 0);
  if (stopMotor2)
    analogWrite(in_3, 0);
}

void encoders() {


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

