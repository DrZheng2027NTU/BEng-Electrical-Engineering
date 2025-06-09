#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

Adafruit_MPU6050 mpu;
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "NODE1";

const int switchPin = 2;
bool controlEnabled = false;
bool lastSwitchState = LOW;
bool stopSignalSent = false;

char lastCommand = 'S';
unsigned long lastSendTime = 0;
unsigned long lastActionTime = 0;
const unsigned long sendInterval = 100;
const unsigned long resendInterval = 300;
const unsigned long holdDuration = 600;

const int bufferSize = 5;
char commandBuffer[bufferSize];
int bufferIndex = 0;

void setup() {
  Serial.begin(115200);
  pinMode(switchPin, INPUT); // 外接下拉，读取高电平启动

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("❌ MPU6050 初始化失败");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  if (!radio.begin()) {
    Serial.println("❌ NRF24 初始化失败");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  if (digitalRead(switchPin) == HIGH) {
    controlEnabled = true;
    Serial.println("⚡ 通电状态 → 程序已启用");
  } else {
    controlEnabled = false;
    Serial.println("⚡ 通电状态 → 程序已禁用");
  }

  stopSignalSent = false;
}

void loop() {
  bool switchState = digitalRead(switchPin);

  if (lastSwitchState == LOW && switchState == HIGH) {
    controlEnabled = !controlEnabled;
    Serial.print(controlEnabled ? "🟢 控制启用" : "🔴 控制禁用");
    Serial.println();
    stopSignalSent = false;
    delay(200);
  }
  lastSwitchState = switchState;

  if (!controlEnabled) {
    if (!stopSignalSent && lastCommand != 'S') {
      char stopCmd = 'S';
      radio.write(&stopCmd, sizeof(stopCmd));
      Serial.println("⛔ 程序禁用 → 发送停止");
      lastCommand = 'S';
      stopSignalSent = true;
    }
    return;
  }

  if (millis() - lastSendTime >= sendInterval) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // 使用真实姿态角计算（角度制）
    float pitch = atan2(a.acceleration.y, sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;
    float roll  = atan2(-a.acceleration.x, a.acceleration.z) * 180.0 / PI;

    char detected = detectCommand(pitch, roll);
    char cmd = getStableCommand(detected);
    bool isAction = (cmd == 'F' || cmd == 'B' || cmd == 'L' || cmd == 'R');

    if (isAction) {
      if (cmd != lastCommand || millis() - lastSendTime >= resendInterval) {
        radio.write(&cmd, sizeof(cmd));
        Serial.print("🔁 指令发送: ");
        Serial.print(cmd);
        Serial.print(" | Pitch=");
        Serial.print(pitch);
        Serial.print("°, Roll=");
        Serial.print(roll);
        Serial.println("°");
        lastCommand = cmd;
        lastSendTime = millis();
      }
      lastActionTime = millis();
    } else {
      if (millis() - lastActionTime > holdDuration && lastCommand != 'S') {
        radio.write(&cmd, sizeof(cmd));
        Serial.println("🛑 姿态回中 → 停止");
        lastCommand = 'S';
        lastSendTime = millis();
      }
    }
  }
}

char detectCommand(float pitch, float roll) {
  if (pitch > 20 && abs(roll) < 15) return 'F';
  if (pitch < -20 && abs(roll) < 15) return 'B';
  if (roll > 20 && abs(pitch) < 15) return 'R';
  if (roll < -20 && abs(pitch) < 15) return 'L';
  return 'S';
}

char getStableCommand(char newCmd) {
  commandBuffer[bufferIndex] = newCmd;
  bufferIndex = (bufferIndex + 1) % bufferSize;

  int countF = 0, countB = 0, countL = 0, countR = 0;
  for (int i = 0; i < bufferSize; i++) {
    switch (commandBuffer[i]) {
      case 'F': countF++; break;
      case 'B': countB++; break;
      case 'L': countL++; break;
      case 'R': countR++; break;
    }
  }

  if (countF >= 3) return 'F';
  if (countB >= 3) return 'B';
  if (countL >= 3) return 'L';
  if (countR >= 3) return 'R';
  return 'S';
}

