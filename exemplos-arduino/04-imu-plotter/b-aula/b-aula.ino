#include <Wire.h>
#include <MPU6050.h>

// SDA = pino 26,  SCL = pino 27
MPU6050 imu;

void setup() {
  Serial.begin(9600);
  Wire.begin(26, 27);
  imu.initialize();
}

void loop() {
  int16_t ax, ay, az;
  imu.getAcceleration(&ax, &ay, &az);

  // limites fixos para o Serial Plotter
  Serial.print(-17000); Serial.print(", ");
  Serial.print(17000);  Serial.print(", ");
  Serial.print(ax);     Serial.print(", ");
  Serial.print(ay);     Serial.print(", ");
  Serial.println(az);

  delay(20);  // ~50 Hz
}

// ─────────────────────────────────────────────
// DESAFIO: mostrar também os dados do giroscópio.
// (dica: imu.getRotation(&gx, &gy, &gz))
// ─────────────────────────────────────────────
