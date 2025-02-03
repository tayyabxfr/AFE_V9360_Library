#include <AFEVANGOV9360.h>

AFEVANGOV9360 AFE;

void setup() {
    Serial.begin(9600);
    delay(50);
    AFE.begin();
      // Initialize the AFE communication
}

void loop() {
    Serial.printf("Voltage: %lu V\n", AFE.voltage());
    Serial.printf("Current: %lu mA\n", AFE.current());
    Serial.printf("Power: %ld W\n", AFE.power());
    delay(1000);
}
  