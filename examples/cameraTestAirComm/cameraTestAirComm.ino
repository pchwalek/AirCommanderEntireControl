/* cameraTestAirComm.ino
*
*  Author: Patrick Chwalek
*  Description: take photo at 5s increments
*/

#include "AirCommanderControl.h" 

AirCommanderControl camCtrl(&Serial2);
void serialEvent2() {
  camCtrl.serialHandler();
}

void setup() {
  Serial.begin(115200);
  camCtrl.begin();

  delay(1000); //initial delay to allow for Air Commander discovery
}

void loop() {
  delay(5000);
  camCtrl.photo();
}
