#define in_1  5 // Left drive motor pin
#define in_2  10 // Left reverse motor pin
#define in_3  9 // Rigth drive motor pin
#define in_4  6 //Right reverse motor pin


#define xOR_LeftPin  3
#define xOR_RightPin 2

#define encoder_B_PinLeft 13
#define encoder_B_PinRight 4




int encoder_PosLeft = 0;
int encoder_PosRight = 0;

int encoder_PrevPos_Left;
int encoder_PrevPos_Right;


int xOR_Value_Left;
int xOR_Value_Right;

int xOR_PrevValue_Left;
int xOR_PrevValue_Right;

int encoder_B_Value_Left = HIGH;
int encoder_B_Value_Right;

int encoder_B_PrevValue_Left;
int encoder_B_PrevValue_Right;

int encoder_A_Value_Left = HIGH;
int encoder_A_Value_Right;

int encoder_A_PrevValue_Left;
int encoder_A_PrevValue_Right;

//int encoderPrevPosLeft = 0;
//int encoderPrevPosRight = 0;



int ticksPies = 832;
int ticksUnidad = 453;
int pies =4;
boolean start = true;
int pwm =180;
double unidad = 12; // pulgadas
int ticksIdeal = pies * ticksPies;
int ticksCalculadosLeft;
int ticksCalculadosRight;



void setup() {
  // put your setup code here, to run once:
  pinMode (in_1, OUTPUT);
  pinMode (in_2, OUTPUT);
  pinMode (in_3, OUTPUT);
  pinMode (in_4, OUTPUT);
  
  pinMode(encoder_B_PinLeft, INPUT);
  pinMode(encoder_B_PinRight, INPUT);
  pinMode(xOR_LeftPin, INPUT);
  digitalWrite(xOR_LeftPin , HIGH);
  pinMode(xOR_RightPin, INPUT);
  digitalWrite(xOR_RightPin, HIGH);

  attachInterrupt(digitalPinToInterrupt(xOR_LeftPin), readxORLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(xOR_RightPin), readxORRight, CHANGE);
  Serial.begin(9600);

    forward(true,true);

}

void loop() {
  // put your main code here, to run repeatedly:




ticksCalculadosLeft = encoder_PosLeft;
ticksCalculadosRight = encoder_PosRight;
reviserLeft();
reviserRight();
checkEncoders();







//printEncoderValue();



















}


void reviserLeft() {
  if (ticksIdeal != ticksCalculadosLeft)
    equalizerLeft();
}

void equalizerLeft() {
  if (ticksIdeal - ticksCalculadosLeft > 0)
    forward(true, false);
  else if (ticksIdeal - ticksCalculadosLeft < 0)
    reverse(true, false);
  else
    pause(true, false);
}

void reviserRight() {
  if (ticksIdeal != ticksCalculadosRight)
    equalizerRight();
}

void equalizerRight() {
  if (ticksIdeal - ticksCalculadosRight > 0)
    forward(false, true);
  else if (ticksIdeal - ticksCalculadosRight < 0)
    reverse(false, true);
  else
    pause(false, true);
}

















void readxORLeft () {

  xOR_PrevValue_Left = xOR_Value_Left;

  encoder_A_PrevValue_Left = encoder_A_Value_Left;
  encoder_B_PrevValue_Left = encoder_B_Value_Left;
  xOR_Value_Left = digitalRead(xOR_LeftPin);
  encoder_B_Value_Left = digitalRead(encoder_B_PinLeft);
  encoder_A_Value_Left = xOR_Value_Left ^ encoder_B_Value_Left;

  encoder_PrevPos_Left = encoder_PosLeft;

  if ((encoder_B_Value_Left ^ encoder_A_PrevValue_Left) & ~(encoder_A_Value_Left ^ encoder_B_PrevValue_Left)) {
    encoder_PosLeft++;
  }

  else {
    encoder_PosLeft--;
  }

}

void readxORRight() {

  xOR_PrevValue_Right = xOR_Value_Right;

  encoder_A_PrevValue_Right = encoder_A_Value_Right;
  encoder_B_PrevValue_Right = encoder_B_Value_Right;
  xOR_Value_Right = digitalRead(xOR_RightPin);
  encoder_B_Value_Right = digitalRead(encoder_B_PinRight);
  encoder_A_Value_Right = xOR_Value_Right ^ encoder_B_Value_Right;

  encoder_PrevPos_Right = encoder_PosRight;

  if ((encoder_B_Value_Right ^ encoder_A_PrevValue_Right) & ~(encoder_A_Value_Right ^ encoder_B_PrevValue_Right)) {
    encoder_PosRight--;
  }

  else {
    encoder_PosRight++;
  }
}


void printEncoderValue() {

  Serial.print("Left Encoder is: ");
  Serial.print(" ");
  Serial.print(encoder_PosLeft);
  Serial.print("    ");
  Serial.print("   Right Encoder is: ");
  Serial.print(" ");
  Serial.println(encoder_PosRight);


}

void forward(boolean left, boolean right) {
  
  if (left) {
    analogWrite(in_1, pwm);
  }
  if (right) {
    analogWrite(in_3, pwm);
  }


}

void reverse(boolean left, boolean right) {
  
  if (left) {
    analogWrite(in_2, pwm);
  }
  if (right) {

    analogWrite(in_4, pwm);
  }
}

void pause(boolean left, boolean right) {
  if (left) {
    digitalWrite(in_1, LOW);
  }
  digitalWrite(in_2, LOW);
  if (right) {
    digitalWrite(in_3, LOW);
  }
  digitalWrite(in_4, LOW);
}

void left() {
  analogWrite(in_1, 0);
  analogWrite(in_2, 0);
  analogWrite(in_3, pwm);
  analogWrite(in_4, 0);
}

void right() {
  analogWrite(in_1, pwm);
  analogWrite(in_2, 0);
  analogWrite(in_3, 0);
  analogWrite(in_4, 0);
}


void checkEncoders() {
  if (encoder_PosRight < encoder_PosLeft) {
    forward(true, false);

  }
  else if (encoder_PosRight > encoder_PosLeft) {
    forward(false, true);
  }
  else
    forward(true, true);

}

