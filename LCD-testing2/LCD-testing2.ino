#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define BUZZER 2

LiquidCrystal_I2C lcd(0x27,16,2); 
// set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myservo;
int i=10;
char a=i;
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  myservo.attach(3);
  myservo.write(0);
}


void loop()
{
  lcd.setCursor(0,0);
  lcd.print("%c",a);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kiranmayee");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Subscribe!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Thank You!");
  delay(1000);
  tone(BUZZER,1000);
  delay(1000);
  myservo.write(360);
  delay(1000);
  myservo.write(0);
  noTone(BUZZER);
  
}
