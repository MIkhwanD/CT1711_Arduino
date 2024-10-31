#include "CT1711.h"
#include <Arduino.h>

float temp = 0;
unsigned long data = 0;

void delay_us(unsigned short int us) {
    delayMicroseconds(us); // Use Arduino delayMicroseconds
}

void ct1711_init(void) {
    pinMode(CT1711_PIN, OUTPUT);          // Set the pin to output mode
    digitalWrite(CT1711_PIN, HIGH);       // Set pin high
    digitalWrite(CT1711_PIN, LOW);        // Pull the pin low
    delay_us(400);                        // Delay for 400 microseconds
    digitalWrite(CT1711_PIN, HIGH);       // Set pin high again
}

unsigned long read_ct1711_data(void) {
    data = 0;

    for (int i = 0; i < 19; i++) {
        digitalWrite(CT1711_PIN, LOW);    // Pull the pin low
        digitalWrite(CT1711_PIN, HIGH);   // Set pin high
        delay_us(16);                     // Delay for 16 microseconds

        pinMode(CT1711_PIN, INPUT);       // Set pin to input to read data
        if (digitalRead(CT1711_PIN) == HIGH) {
            data <<= 1;
            data += 1;
        } else {
            data <<= 1;
        }
        pinMode(CT1711_PIN, OUTPUT);      // Set pin back to output mode
        digitalWrite(CT1711_PIN, HIGH);   // Set pin high
        delay_us(34);                     // Delay for 34 microseconds
    }

    return data;
}

void StartgetTemp(void) {
    ct1711_init(); // Initialize CT1711
    delay(150);    // Wait for 150 ms (Arduino doesn't have hardware timers like STM32 HAL)
}

float getTemp(void) {
    unsigned long temp_data = 0;   // Local variable to store temperature data
    unsigned long temp_value = 0;  // Local variable to store temperature value
    temp_data = read_ct1711_data(); // Read the 19-bit data from CT1711
    temp_value = temp_data & 0x0000FFFF; // Extract 17-bit data

    if ((temp_data & 0x00060000) == 0x00000000) { // Check if data is valid
        if ((temp_data & 0x00010000) == 0x00000000) {  // Check if temperature is positive
            temp = temp_value * Sensor_resolution;
        } else { // Negative temperature
            temp = -temp_value * Sensor_resolution;
        }
    }

    return temp;
}

