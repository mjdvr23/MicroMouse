

char  bt_val;
const int in_1 = 3; // Left drive motor pin
const int in_2 = 5; // Left reverse motor pin
const int in_3 = 10;  // Rigth drive motor pin
const int in_4 = 9;  // Right reverse motor pin

int leftMotorPwm = 150;
int rightMotorPwm = 150;
int delayTime = 1000;


int val;
int encoder0PinA = 12;
int encoder0PinB = 13;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;


void setup() {
  // put your setup code here, to run once:


  pinMode (in_1, OUTPUT);
  pinMode (in_2, OUTPUT);
  pinMode (in_3, OUTPUT);
  pinMode (in_4, OUTPUT);

  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  Serial.begin (9600);

}

void loop() {
  // put your main code here, to run repeatedly:


drive(leftMotorPwm, rightMotorPwm);




if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    Serial.println (encoder0Pos);

  }
  encoder0PinALast = n;
  
  
  



}







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

void pausa() {

  analogWrite(in_1, 0);
  analogWrite(in_2, 0);
  analogWrite(in_3, 0);
  analogWrite(in_4, 0);
}


