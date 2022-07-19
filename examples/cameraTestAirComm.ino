#include "AirCommanderControl.h" 

AirCommanderControl camCtrl(&Serial2);
void serialEvent2() {
  camCtrl.serialHandler();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  camCtrl.begin();
}

void loop() {
  delay(5000);
  camCtrl.photo();
}
