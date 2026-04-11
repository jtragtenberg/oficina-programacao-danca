// ponto de partida: sensor+plotter do ciclo anterior
// instalar também: "OSC" by Adrian Freed

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  Wire.begin(26, 27);  // SDA=26, SCL=27

  if (!mpu.begin()) {
    Serial.println("Sensor MPU6050 não encontrado!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // adicionar aqui o código OSC do exemplo ESP8266sendMessage

  delay(20);
}
