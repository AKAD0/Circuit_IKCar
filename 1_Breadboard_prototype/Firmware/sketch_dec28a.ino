#include "IRremote.h"
#include "Servo.h"

IRrecv irrecv(11);
Servo myservo;
decode_results results;
unsigned long code;

void motor( unsigned long code){
  if ( code==16718055){ //forward hard
    Serial.println("HIGH to pin 13");
    digitalWrite(13,1);
    delay(2000);
  };
  if ( code==16726215){ //forward easy
    Serial.println("HIGH to pin 13");
    digitalWrite(13,1);
    delay(500);
  };
};

void servo( unsigned long code){
  if ( code==16724175){
    myservo.write(30); //turn left hard
    delay(10);
  }
  if ( code==16743045){
    myservo.write(150);//turn right hard
    delay(10);
  }
  if ( code==16716015){
    myservo.write(60); //turn left med
    delay(10);
  }
  if ( code==16734885){
    myservo.write(120);//turn right med
    delay(10);
  }
  if ( code==16728765){
    myservo.write(75); //turn left easy
    delay(10);
  }
  if ( code==16732845){
    myservo.write(105);//turn right easy
    delay(10);
  }
  if ( code==16730805){
    myservo.write(90);//center
    delay(10);
  }
};

void setup() {
  Serial.begin(9600);
  //pins config: pinMode(<pin>,<mode>)
  pinMode(A5, INPUT_PULLUP); //motor button
  pinMode(13, OUTPUT); //motor relay

  //apparel config
  irrecv.enableIRIn(); //receive init
  myservo.attach(9); //setting servo in 9th pin
}

void loop() {
  boolean button1 = !(digitalRead(A5));
  int val;

  //Button
  if (button1==1){
    digitalWrite(13,1);
  }
  else{
    digitalWrite(13,0);
  };

  //IR receiver: motor(),servo()
  if ( irrecv.decode( &results)){ //if there is a receival
    code = results.value;
    Serial.println( code);
    motor( code);
    servo( code);
    irrecv.resume();
  };
}