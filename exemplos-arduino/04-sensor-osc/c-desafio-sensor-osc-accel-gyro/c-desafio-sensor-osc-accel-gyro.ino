// ─────────────────────────────────────────────────────────────────────────────
// DEPENDÊNCIAS — instalar via Arduino IDE: Tools → Manage Libraries...
//
// 1. OSC  (por CNMAT — Yotam Mann e Adrian Freed)
//    buscar: "OSC"  autor: CNMAT
//
// 2. Adafruit MPU6050  (por Adafruit)
//    buscar: "Adafruit MPU6050"
//    instala automaticamente: Adafruit Unified Sensor e Adafruit BusIO
//
// 3. Bounce2  (por Thomas O Fredericks)
//    buscar: "Bounce2"
//
// WiFi, WiFiUdp, Wire e EEPROM já vêm com o core ESP32 —
// não precisam ser instalados separadamente.
//
// PLACA: Tools → Board → esp32 → ESP32 Dev Module
// ─────────────────────────────────────────────────────────────────────────────
// Envia acelerômetro e giroscópio via OSC por UDP.
// Endereços OSC:
//   /giromin/ID/a  →  x, y, z  normalizado (-1 a 1)
//   /giromin/ID/g   →  x, y, z  normalizado (-1 a 1)
//   /giromin/ID/b1  →  1 ao apertar, 0 ao soltar
//
// CALIBRAÇÃO: segure o botão ao ligar para calibrar e salvar na EEPROM.
// ─────────────────────────────────────────────────────────────────────────────

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Bounce2.h>
#include <EEPROM.h>

const char* ssid     = "giromin2";
const char* password = "dervishmaria";

const int ID        = 1;
const int BOTAO_PIN = 5;

IPAddress destIP(192, 168, 0, 101);
const int destPort  = 9999;
const int localPort = 8888;

WiFiUDP udp;
Adafruit_MPU6050 mpu;
Bounce botao;

// ── Offsets de calibração (salvos na EEPROM) ──────────────────────────────
struct Offsets {
  float ax, ay, az;
  float gx, gy, gz;
};
Offsets offsets = {0, 0, 0, 0, 0, 0};

#define EEPROM_SIZE    sizeof(Offsets)
#define EEPROM_ADDR    0
#define CALIB_SAMPLES  200

void salvarOffsets() {
  EEPROM.put(EEPROM_ADDR, offsets);
  EEPROM.commit();
}

void carregarOffsets() {
  EEPROM.get(EEPROM_ADDR, offsets);
}

void calibrar() {
  Serial.println("Calibrando — mantenha o sensor parado...");
  delay(3000); 
  double sax=0, say=0, saz=0, sgx=0, sgy=0, sgz=0;
  for (int i = 0; i < CALIB_SAMPLES; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sax += a.acceleration.x;
    say += a.acceleration.y;
    saz += a.acceleration.z;
    sgx += g.gyro.x;
    sgy += g.gyro.y;
    sgz += g.gyro.z;
    delay(5);
  }
  offsets.ax = sax / CALIB_SAMPLES;
  offsets.ay = say / CALIB_SAMPLES;
  offsets.az = saz / CALIB_SAMPLES;
  offsets.gx = sgx / CALIB_SAMPLES;
  offsets.gy = sgy / CALIB_SAMPLES;
  offsets.gz = sgz / CALIB_SAMPLES;
  offsets.az -= 9.81;
  salvarOffsets();
  Serial.println("Calibração salva.");
}

// ── Normalização ──────────────────────────────────────────────────────────
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

// ── Setup ─────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);
  carregarOffsets();

  botao.attach(BOTAO_PIN, INPUT_PULLUP);
  botao.interval(10);

  Wire.begin(21, 22);
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Se botão estiver apertado ao ligar → calibrar
  if (digitalRead(BOTAO_PIN) == LOW) {
    calibrar();
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nIP: " + WiFi.localIP().toString());

  udp.begin(localPort);
}

// ── Loop ──────────────────────────────────────────────────────────────────
void loop() {
  botao.update();

  // Botão: envia OSC /giromin/ID/b1 — 1 ao apertar, 0 ao soltar
  if (botao.fell() || botao.rose()) {
    String addr = "/giromin/" + String(ID) + "/b1";
    OSCMessage msg(addr.c_str());
    msg.add(botao.fell() ? (int32_t)1 : (int32_t)0);
    udp.beginPacket(destIP, destPort);
    msg.send(udp);
    udp.endPacket();
    msg.empty();
  }

  // Sensor com offset de calibração aplicado
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float ax = a.acceleration.x - offsets.ax;
  float ay = a.acceleration.y - offsets.ay;
  float az = a.acceleration.z - offsets.az;
  float gx = g.gyro.x         - offsets.gx;
  float gy = g.gyro.y         - offsets.gy;
  float gz = g.gyro.z         - offsets.gz;

  String accel_addr = "/giromin/" + String(ID) + "/a";
  OSCMessage msgAccel(accel_addr.c_str());
  msgAccel.add(normalizeAccel(ax));
  msgAccel.add(normalizeAccel(ay));
  msgAccel.add(normalizeAccel(az));
  udp.beginPacket(destIP, destPort);
  msgAccel.send(udp);
  udp.endPacket();
  msgAccel.empty();

  String gyro_addr = "/giromin/" + String(ID) + "/g";
  OSCMessage msgGyro(gyro_addr.c_str());
  msgGyro.add(normalizeGyro(gx));
  msgGyro.add(normalizeGyro(gy));
  msgGyro.add(normalizeGyro(gz));
  udp.beginPacket(destIP, destPort);
  msgGyro.send(udp);
  udp.endPacket();
  msgGyro.empty();

  delay(10);
}
