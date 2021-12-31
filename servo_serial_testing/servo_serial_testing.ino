#include<Servo.h>
#include <SPI.h>
#include <HX711_ADC.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define open 45
#define close 0
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin
#define BUZZER 2 //buzzer pin
LiquidCrystal_I2C lcd(0x27,16,2);
HX711_ADC LoadCell(HX711_dout, HX711_sck);
Servo myservo;
const int calVal_eepromAdress = 0;
unsigned long t = 0;
int val = 10;
char d;
int flag = 0;
int pos =0;
void setup() {
  // put your setup code here, to run once:
lcd.init();                      // initialize the lcd 
lcd.backlight();
Serial.begin(9600);
SPI.begin();      // Initiate  SPI bus
pinMode(5,OUTPUT);
pinMode(BUZZER, OUTPUT);
noTone(BUZZER);
Serial.println();
myservo.attach(9); 
//myservo.write(0);
LoadCell.begin();
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
  #if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
  #endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

void loop() {
  //flag = 0;
  //lcd.setCursor(0,0);
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  d=Serial.read();
}
if(d=='a')
{
      //Serial.print(d);
      //delay(100);
      /*for(pos=0;pos<=90;pos+=5)
       {
        myServo.write(pos);
       delay(20);
       }*/
       //myservo.write(90);
       for (pos = close; pos <= open; pos ++) 
       { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
       }
       delay(50);
       //myservo.detach();
       //delay(500);
       //myServo.attach(9);
       //tone(BUZZER, 500);
       while(1)
       {
            lcd.setCursor(0,0);
            static boolean newDataReady = 0;
            const int serialPrintInterval = 0;
            if (LoadCell.update()) newDataReady = true;
                Serial.println("in the loop");
            if (newDataReady) 
             {
                if(millis() > t + serialPrintInterval) 
                {
                    float i = LoadCell.getData();
                    lcd.print(String("Load Valu:")+i);
                    Serial.print("Load_cell output val: ");
                    Serial.println(i);
                    newDataReady = 0;
                    t = millis();
                    if(i>150)
                    {
                        flag = 1;
                        break;
                    }
                }
             }
             if(flag)
             {
                break;
             }
             delay(50);
       }
       /*for(pos=90;pos>=0;pos-=5)
       {  
          myServo.write(pos);
          delay(20);
       }*/
       //myServo.write(0);
     // myservo.attach(9);
      //myservo.write(0);
      // close(myservo,pos);
//      for(int pos =0;pos<=180;pos++)
//      {
//        myservo.write(pos);
//        delay(20);
//      }
       for (int i= open; i >= close; i --)
       { // goes from 180 degrees to 0 degrees
              myservo.write(i);              // tell servo to go to position in variable 'pos'
              delay(15);                       // waits 15ms for the servo to reach the position
       }
     
//       myServo.detach();
        delay(50);
        // myServo.attach(9);
//       Serial.println("servo back to zero");
//       digitalWrite(LED_G, LOW);
       if (Serial.available() > 0)
       {
          char inByte = Serial.read();
          if (inByte == 't') LoadCell.tareNoDelay();
       }
       if (LoadCell.getTareStatus() == true)
       {
          Serial.println("Tare complete");
       }
}
else 
{
    Serial.println(" Access denied");
//    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
//    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
}
   d="";
}
//void close(Servo myservo,int pos)
//{
//  for(int pos=90;pos>=0;pos-=1)
//  {
//    myservo.write(pos);
//    delay(15);
//  }
//}
