#include "dhtnew.h"
#include "HT16K33.h"

HT16K33 seg(0x70);
DHTNEW mySensor(5);

bool showTemp = true;

unsigned long previousMillis = 0;

const unsigned long interval = 5000;

void setup()
{
  Wire.begin();
  Wire.setClock(100000);
  seg.begin();
  seg.displayOn();
  seg.setBrightness(0);
  mySensor.setSuppressError(true);
}

void loop()
{
  int chk = mySensor.read();
  if (chk == DHTLIB_WAITING_FOR_READ) {
    unsigned long currentMillis = millis();
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      previousMillis = currentMillis;
      if (showTemp) {
        seg.displayUnit(mySensor.getTemperature(), 1, HT16K33_DEGREE);
        showTemp = !showTemp;
      } else {
        seg.displayUnit(mySensor.getHumidity(), 1);
        showTemp = !showTemp;
      }
    }
  }
}
