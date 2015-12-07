#define in_1  5 // Left drive motor pin
#define in_2  6 // Left reverse motor pin
#define in_3  9 // Rigth drive motor pin
#define in_4  10 //Right reverse motor pin
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

int unidad = 1;
int ticksUnidad = 452;
int ticksIdeal = unidad * ticksUnidad;
int pwm = 180;
boolean turn = true;
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

 forward(true, true);

  //analogWrite(in_1,pwm);
  //analogWrite(in_4,pwm);
}

void loop() {
  // put your main code here, to run repeatedly:
if(turn){
forwardPorUnidad();
}
if(encoder_PosLeft >= ticksIdeal && encoder_PosRight >= ticksIdeal)
{
  encoder_PosLeft = 0;
  encoder_PosRight = 0;
  turnRight();
  turn = false;
  }



}


void forwardPorUnidad() {
  checkEncoders();
  if (encoder_PosLeft >= ticksIdeal )
    pause(true, false);
  if (encoder_PosRight >= ticksIdeal)
    pause(false, true);
 
}

void turnRight() {


  if (encoder_PosLeft >= 225)
    analogWrite(in_1, 0);
  if (encoder_PosRight <= -225)
    analogWrite(in_4, 0);

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


