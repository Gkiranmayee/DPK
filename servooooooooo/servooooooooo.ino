#include <Servo.h>
Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  //myServo.write(0);
  // put your setup code here, to run once:

}

void loop() {
    myServo.write(0);
    Serial.println("delay");
    delay(500);
    myServo.detach();
   // delay(100);
    myServo.attach(9);
    myServo.write(180);
    Serial.println("Second delay");
    delay(500);
    myServo.detach();
    //delay(100);
    myServo.attach(9);
    //myServo.write(0);
    Serial.println("servo turned back");
  // put your main code here, to run repeatedly:    
  
}
