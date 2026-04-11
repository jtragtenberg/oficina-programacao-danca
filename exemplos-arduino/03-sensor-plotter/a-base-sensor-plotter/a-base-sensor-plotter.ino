// ─────────────────────────────────────────────
// 04 · Sensor MPU6050 + Serial Plotter
// ─────────────────────────────────────────────
// Biblioteca necessária: Adafruit MPU6050
// Instalar em: Tools → Manage Libraries → buscar "Adafruit MPU6050"
//
// Abra: Tools → Serial Plotter para ver o gráfico em tempo real.

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

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

  // Formato com rótulos — o Serial Plotter mostra cada linha como uma curva separada
  Serial.print("AccelX:"); Serial.print(a.acceleration.x);
  Serial.print(",AccelY:"); Serial.print(a.acceleration.y);
  Serial.print(",AccelZ:"); Serial.print(a.acceleration.z);
  Serial.print(",GyroX:"); Serial.print(g.gyro.x);
  Serial.print(",GyroY:"); Serial.print(g.gyro.y);
  Serial.print(",GyroZ:"); Serial.println(g.gyro.z);

  delay(10);
}

// ─────────────────────────────────────────────
// DESAFIO: segure o sensor e mova o corpo.
// Identifique qual dado (AccelX, AccelY, AccelZ,
// GyroX, GyroY, GyroZ) corresponde a qual movimento.
// ─────────────────────────────────────────────
