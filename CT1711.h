#ifndef __CT1711_H
#define __CT1711_H

#define Sensor_resolution    0.00432000  // Sensor resolution (default = 0.00390625)
#define CT1711_PIN           25          // Pin number for CT1711 sensor (change as needed)

void delay_us(unsigned short int us);
void ct1711_init(void);
float getTemp(void);
unsigned long read_ct1711_data(void);
void StartgetTemp(void);

#endif
