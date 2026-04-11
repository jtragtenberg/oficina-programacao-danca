#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const char* ssid     = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

IPAddress destIP(192, 168, 1, 255);
const int destPort  = 9999;
const int localPort = 8888;

WiFiUDP udp;
Adafruit_MPU6050 mpu;

float normalizeAccel(Adafruit_MPU6050 &mpu, float value) {
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

float normalizeGyro(Adafruit_MPU6050 &mpu, float value) {
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

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nIP: " + WiFi.localIP().toString());

  udp.begin(localPort);

  Wire.begin(26, 27);  // SDA=26, SCL=27
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  OSCMessage msg("/giromin/accel");
  msg.add(normalizeAccel(mpu, a.acceleration.x));
  msg.add(normalizeAccel(mpu, a.acceleration.y));
  msg.add(normalizeAccel(mpu, a.acceleration.z));
  udp.beginPacket(destIP, destPort);
  msg.send(udp);
  udp.endPacket();
  msg.empty();

  delay(20);
}

// ─────────────────────────────────────────────
// DESAFIO: adicionar também o giroscópio.
// Enviar em "/giromin/gyro" os valores
// g.gyro.x, g.gyro.y, g.gyro.z
// ─────────────────────────────────────────────
