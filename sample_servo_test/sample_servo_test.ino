#include<Servo.h>
Servo servo1;
int servoPin=9;
void setup(){
  Serial.begin(9600);
  servo1.attach(servoPin);
}
void loop(){
  servo1.write(0);
  delay(500);
  Serial.println("Inside loop");
  servo1.write(90);
  delay(500);

}
