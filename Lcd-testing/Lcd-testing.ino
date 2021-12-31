#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x24, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop()
{
	// Do nothing here...
 lcd.clear();
  lcd.print("Kiranmayee");
  lcd.setCursor (0,1); // go to start of 2nd line
 lcd.print("Hello World!");
  //lcd.print(millis() / 1000);
  delay(500);
}
