#include <Arduino.h>
#include <CT1711.h>

void setup()
{
  pinMode(15, OUTPUT);
  pinMode(CT1711_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  StartgetTemp();                 // Start the process of reading temperature
  delay(150);                     // Wait for 150ms to let the sensor initialize and provide data
  float temperature = getTemp();  // Read temperature from the CT1711 sensor

  // Send temperature to Serial
  Serial.println("Temp : "+ String(temperature, 2)+"°C");

  // Check temperature threshold and control pin 15
   if (temperature >= 36.0) {
    digitalWrite(15, HIGH);
  } else {
    digitalWrite(15, LOW);
  }
  delay(100);
}
