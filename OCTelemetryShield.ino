#include <SPI.h>
#include <Adafruit_MAX31855.h>

// ITS-90 conversion constants
#include "ITS90.h"

// Example creating a thermocouple instance with hardware SPI (Uno/Mega only)
// on a given CS pin.
#define CS1    2
#define CS2    3
Adafruit_MAX31855 th1(CS1);
Adafruit_MAX31855 th2(CS2);

int v1pin = A0;
int v2pin = A1;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  delay(2000);
  // wait for MAX chip to stabilize
  Serial1.println("#Millis,TC1Internal(C),TC1External(C),TC1Corrected(C),TC2Internal(C),TC2External(C),TC2Corrected(C),Voltage1(V),Voltage2(V)");
  delay(500);
}

void loop() {
  
  double t1, t1_amb, t2, t2_amb;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;
  
    t1 = th1.readCelsius();
    t1_amb = th1.readInternal();
    t2 = th2.readCelsius();
    t2_amb = th2.readInternal();
  
    Serial1.print(currentMillis);
    Serial1.print(",");
    
    Serial1.print(t1_amb);
    Serial1.print(",");
   
    if (isnan(t1)) {
       Serial1.print("");
    } else {
       Serial1.print(t1);
    }
    Serial1.print(",");
  
    if (isnan(t1)) {
       Serial1.print("");
    } else {
       Serial1.print(correctedTemperature(t1, t1_amb));
    }
    Serial1.print(",");
  
    Serial1.print(t2_amb);
    Serial1.print(",");
   
    if (isnan(t2)) {
       Serial1.print("");
    } else {
       Serial1.print(t2);
    }
    Serial1.print(",");
  
    if (isnan(t2)) {
       Serial1.print("");
    } else {
       Serial1.print(correctedTemperature(t2, t2_amb));
    }
    Serial1.print(",");
    
    
    Serial1.print(getVoltage(A0));
    Serial1.print(",");
    
    Serial1.print(getVoltage(A1));
    
    Serial1.println("");

  } // end of internal loop

}

float getVoltage(int pin) {
  int sensorValue;
  sensorValue = analogRead(pin);
  float multiplier = (10.0 + 33.2) / 10.0;
  float reading;
  reading = 5.0 * sensorValue / 1024.0 * multiplier;
  return reading;
}

float voltageFromMax31855(float t, float t_amb) {
  float a = 41.276;   // uV/C
  return a * (t - t_amb);
}

// ITS-90 conversion, temperature -> voltage
float voltageFromTemperature(float t) {
  float v = 0;
  if (t <= 0) {
    v = c_0 + (c_1*t) + (c_2*pow(t,2)) + (c_3*pow(t,3)) + (c_4*pow(t,4)) + (c_5*pow(t,5)) + (c_6*pow(t,6)) + (c_7*pow(t,7)) + (c_8*pow(t,8)) + (c_9*pow(t,9)) + (c_10*pow(t,10));
  } else {
    v = d_0 + (d_1*t) + (d_2*pow(t,2)) + (d_3*pow(t,3)) + (d_4*pow(t,4)) + (d_5*pow(t,5)) + (d_6*pow(t,6)) + (d_7*pow(t,7)) + (d_8*pow(t,8)) + (d_9*pow(t,9)) +
        f0 * exp(f1 * pow(t-126.9686,2));
  }
  return v;
}

// ITS-90 conversion, voltage -> temperature
float temperatureFromVoltage(float v) {
  float t = 0;
  if (v <= 0) {
    t = x_0 + (x_1*v) + (x_2*pow(v,2)) + (x_3*pow(v,3)) + (x_4*pow(v,4)) + (x_5*pow(v,5)) + (x_6*pow(v,6)) + (x_7*pow(v,7)) + (x_8*pow(v,8));
  } else {
    t = y_0 + (y_1*v) + (y_2*pow(v,2)) + (y_3*pow(v,3)) + (y_4*pow(v,4)) + (y_5*pow(v,5)) + (y_6*pow(v,6)) + (y_7*pow(v,7)) + (y_8*pow(v,8)) + (y_9*pow(v,9));
  }
  return t;
}

float correctedTemperature(float t, float t_amb) {
  float v = voltageFromMax31855(t, t_amb);
  float v_amb = voltageFromTemperature(t_amb);
  return temperatureFromVoltage(v + v_amb);
}

