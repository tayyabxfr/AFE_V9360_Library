#include <AFEVANGOV9360.h>

AFEVANGOV9360 AFE;

void setup() {
    Serial.begin(9600);
    delay(50);
    AFE.begin();
      // Initialize the AFE  
}

void loop() {

    float voltage = AFE.voltage() / 200087.0;
    voltage = (voltage < 0.21) ? 0.00 : voltage;  
    float current = (AFE.current() / 205.0) / 1000.0;
    current = (current <= 0.02) ? 0.00 : current; 
    int32_t power=  AFE.power();                                                                                                                                     
    
    float app = voltage * current ;
      
    Serial.printf("Voltage : %.2f V\n",voltage);
    Serial.printf("Current : %.2f A\n",current);
    if (current == 0.00)
    {
    power = 0.0;
    }
    Serial.printf("Power : %ld W\n",power);
    float pf = abs(power)/app;
    if (pf > 1.00 && pf < 1.02) 
    {
      Serial.printf("pf : 1.00\n");
    }
    else if(pf > 1.02)
    {
      Serial.printf("pf : nan\n");
    }
    else
    {
      Serial.printf("pf : %.2f\n",pf);
    }
    delay(1000);
}
  