#include <Servo.h>
Servo myservo;
int pos=0;
int flag =0;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  //myservo.write(0);
  // put your setup code here, to run once:

}

void loop() {
//    myServo.write(0);
//    Serial.println("delay");
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
  }
    //delay(100);
//    myServo.detach();
//   // delay(100);
//    myServo.attach(9);
//    myServo.write(180);
//    Serial.println("Second delay");
//     while(1)
//     {
//      for(int i=0;i<20;i++)
//      {
//        Serial.print(String(i));
//        if(i==10)
//        {
//          Serial.println("in the loop");
//          flag = 1;
//        }
//      }
//      if(flag)
//      {
//        break;
//      }
//     }
     delay(100);
     Serial.println("after delay");
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
  }
    delay(50);
//    myServo.detach();
//    //delay(100);
//    myServo.attach(9);
//    //myServo.write(0);
//    Serial.println("servo turned back");
//  // put your main code here, to run repeatedly:    
  
}
