#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <EEPROM.h>

#define EEPROM_SIZE 24  // 6 floats × 4 bytes

Adafruit_MPU6050 mpu;

float axOff=0, ayOff=0, azOff=0;
float gxOff=0, gyOff=0, gzOff=0;

float normalizeAccel(float value) {
  float maxG;
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:  maxG =  2.0; break;
    case MPU6050_RANGE_4_G:  maxG =  4.0; break;
    case MPU6050_RANGE_8_G:  maxG =  8.0; break;
    case MPU6050_RANGE_16_G: maxG = 16.0; break;
    default:                 maxG =  8.0;
  }
  return constrain(value / (maxG * 9.81), -1.0, 1.0);
}

float normalizeGyro(float value) {
  float maxDeg;
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:  maxDeg =  250.0; break;
    case MPU6050_RANGE_500_DEG:  maxDeg =  500.0; break;
    case MPU6050_RANGE_1000_DEG: maxDeg = 1000.0; break;
    case MPU6050_RANGE_2000_DEG: maxDeg = 2000.0; break;
    default:                     maxDeg =  500.0;
  }
  return constrain(value / (maxDeg * DEG_TO_RAD), -1.0, 1.0);
}

void calibrar() {
  Serial.println("Calibrando... mantenha o sensor parado.");
  const int N = 500;
  double sax=0, say=0, saz=0, sgx=0, sgy=0, sgz=0;
  for (int i = 0; i < N; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sax += a.acceleration.x;
    say += a.acceleration.y;
    saz += a.acceleration.z;
    sgx += g.gyro.x;
    sgy += g.gyro.y;
    sgz += g.gyro.z;
    delay(2);
  }
  axOff = sax / N;
  ayOff = say / N;
  azOff = saz / N - 9.81;  // remove gravidade do eixo Z
  gxOff = sgx / N;
  gyOff = sgy / N;
  gzOff = sgz / N;
  Serial.println("Calibração concluída.");
}

void salvarCalibracao() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(0,  axOff); EEPROM.put(4,  ayOff);
  EEPROM.put(8,  azOff); EEPROM.put(12, gxOff);
  EEPROM.put(16, gyOff); EEPROM.put(20, gzOff);
  EEPROM.commit();
  EEPROM.end();
  Serial.println("Calibração salva na EEPROM.");
}

void carregarCalibracao() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0,  axOff); EEPROM.get(4,  ayOff);
  EEPROM.get(8,  azOff); EEPROM.get(12, gxOff);
  EEPROM.get(16, gyOff); EEPROM.get(20, gzOff);
  EEPROM.end();
  Serial.println("Calibração carregada da EEPROM.");
}

void setup() {
  Serial.begin(115200);

  pinMode(5, INPUT_PULLUP);

  Wire.begin(21, 22);
  if (!mpu.begin()) {
    Serial.println("Sensor MPU6050 não encontrado!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // segurar botão no pino 5 durante o reset para recalibrar
  if (digitalRead(5) == LOW) {
    calibrar();
    salvarCalibracao();
  } else {
    carregarCalibracao();
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print(-1.0); Serial.print(",");
  Serial.print(1.0);  Serial.print(",");
  Serial.print(normalizeAccel(a.acceleration.x - axOff)); Serial.print(",");
  Serial.print(normalizeAccel(a.acceleration.y - ayOff)); Serial.print(",");
  Serial.print(normalizeAccel(a.acceleration.z - azOff)); Serial.print(",");
  Serial.print(normalizeGyro(g.gyro.x - gxOff)); Serial.print(",");
  Serial.print(normalizeGyro(g.gyro.y - gyOff)); Serial.print(",");
  Serial.println(normalizeGyro(g.gyro.z - gzOff));

  delay(10);
}

// ─────────────────────────────────────────────
// DESAFIO: usar os dados do acelerômetro para
// controlar a velocidade do piscar do LED.
// ─────────────────────────────────────────────
