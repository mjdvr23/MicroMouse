#define in_1  6 // Left drive motor pin
#define in_2  5 // Left reverse motor pin
#define in_3  10  // Rigth drive motor pin
#define in_4  9  // Right reverse motor pin

#define xOR_LeftPin  3
#define xOR_RightPin 2

#define encoder_B_PinLeft 13
#define encoder_B_PinRight 4

int encoder_PosLeft= 0;
int encoder_PosRight = 0;





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
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readxORLeft (){
 
  }

void readxORRight(){

}

 
