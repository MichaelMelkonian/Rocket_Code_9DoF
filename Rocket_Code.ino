#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);

int sensorPin = 0;
const int chipSelect = 10;

void setup(void)
{
  Serial.begin(9600);
  //while (!Serial) {
  //  delay(1);
  //}
  if(!accelmag.begin(ACCEL_RANGE_4G))
  {
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while(1);
  }
  if(!gyro.begin())
  {
    Serial.println("Ooops, no FXAS21002C detected ... Check your wiring!");
    while(1);
  }
  
  Serial.print("Turning on the card\n");
  if (!SD.begin(chipSelect)) {
    Serial.println("Did not work :l\n");
    while(1);
  }
  Serial.println("Congratulations, card works!");
  
}

void loop()
{
  File dataFile = SD.open("myFile.txt", FILE_WRITE);

  
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.910) * 100 ;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  
  sensors_event_t aevent, mevent, event;
  gyro.getEvent(&event);
  accelmag.getEvent(&aevent, &mevent);
  
  
  /* Display the accel results (acceleration is measured in m/s^2) */
  Serial.println("");
  Serial.println("Acceleration Values");
  Serial.print("X: "); Serial.print(aevent.acceleration.x, 4); Serial.print("  ");
  Serial.print("Y: "); Serial.print(aevent.acceleration.y, 4); Serial.print("  ");
  Serial.print("Z: "); Serial.print(aevent.acceleration.z, 4); Serial.print("  ");
  Serial.println("m/s^2");

  /* Display the mag results (mag data is in uTesla) */
  Serial.print("Magnetic Values\n");
  Serial.print("X: "); Serial.print(mevent.magnetic.x, 1); Serial.print("  ");
  Serial.print("Y: "); Serial.print(mevent.magnetic.y, 1); Serial.print("  ");
  Serial.print("Z: "); Serial.print(mevent.magnetic.z, 1); Serial.print("  ");

  Serial.println("uT");

  /* Display the results (speed is measured in rad/s) */
  Serial.println("Rotational Values");
  Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("  ");
  Serial.println("rad/s ");
  
  /* Display the results (speed is measured in C & F) */
  Serial.println("Temperature/Volt Values");
  Serial.print(temperatureC); Serial.println(" degrees C");
  Serial.print(temperatureF); Serial.println(" degrees F");
  Serial.print(voltage); Serial.println(" volts");

  Serial.println("");

  if (dataFile) {
    dataFile.print(aevent.acceleration.x, 4);
    dataFile.print(" ");
    dataFile.print(aevent.acceleration.y, 4);
    dataFile.print(" ");
    dataFile.print(aevent.acceleration.z, 4);
    dataFile.print(" ");
    dataFile.print(mevent.magnetic.x, 1);
    dataFile.print(" ");
    dataFile.print(mevent.magnetic.y, 1);
    dataFile.print(" ");
    dataFile.print(mevent.magnetic.z, 1);
    dataFile.print(" ");
    dataFile.print(event.gyro.x);
    dataFile.print(" ");
    dataFile.print(event.gyro.y);
    dataFile.print(" ");
    dataFile.print(event.gyro.z);
    dataFile.print(" ");
    dataFile.print(temperatureC);
    dataFile.print(" ");
    dataFile.print(temperatureF);
    dataFile.print(" ");
    dataFile.print(voltage);
    dataFile.println();
    dataFile.close();
    Serial.print("Accel. - X: ");
    Serial.print(aevent.acceleration.x, 4);
    Serial.print(" ");
    Serial.print("Accel. - Y ");
    Serial.print(aevent.acceleration.y, 4);
    Serial.print(" ");
    Serial.print("Accel. - Z ");
    Serial.print(aevent.acceleration.z, 4);
    Serial.print(" ");
    Serial.print("Mag. - X ");
    Serial.print(mevent.magnetic.x, 1);
    Serial.print(" ");
    Serial.print("Mag. - Y ");
    Serial.print(mevent.magnetic.y, 1);
    Serial.print(" ");
    Serial.print("Mag. - Z ");
    Serial.print(mevent.magnetic.z, 1);
    Serial.print(" ");
    Serial.print("Rads. - X ");
    Serial.print(event.gyro.x);
    Serial.print(" ");
    Serial.print("Rads. - Y ");
    Serial.print(event.gyro.y);
    Serial.print(" ");
    Serial.print("Rads. - Z ");
    Serial.print(event.gyro.z);
    Serial.print(" ");
    Serial.print("Temp. - C ");
    Serial.print(temperatureC);
    Serial.print(" ");
    Serial.print("Temp. - F ");
    Serial.print(temperatureF);
    Serial.print(" ");
    Serial.print("Volt. ");
    Serial.print(voltage);
    Serial.println();
  }
  else {
    Serial.println("Didnt work, try again");
  }
  
}
