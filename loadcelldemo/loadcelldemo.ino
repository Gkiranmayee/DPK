#include "HX711.h"
HX711 cell;
void setup(){
Serial.begin(3,2);
}
void loop(){
Serial.println(cell.read());
}
