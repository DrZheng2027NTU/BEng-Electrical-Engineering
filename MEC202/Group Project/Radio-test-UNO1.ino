#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "NODE1";

// 超声波模块接线
const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int obstacleThreshold = 10; // 障碍距离阈值（cm）

char lastCommand = 'S';
char filteredCommand = 'S';

unsigned long lastUltrasonicCheck = 0;
const unsigned long ultrasonicInterval = 100;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if (!radio.begin()) {
    Serial.println("❌ NRF 初始化失败");
    while (1);
  }

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("✅ UNO 接收器启动，支持避障逻辑");
}

void loop() {
  // 读取无线指令
  if (radio.available()) {
    char cmd;
    radio.read(&cmd, sizeof(cmd));
    lastCommand = cmd;
    Serial.print("📡 接收命令: ");
    Serial.println(cmd);
  }
  // 周期性测距避障
 if (millis() - lastUltrasonicCheck >= ultrasonicInterval) {
   lastUltrasonicCheck = millis();
   long distance = getDistanceCM();

    Serial.print("📏 距离: ");
    Serial.print(distance);
    Serial.println(" cm");

    // 对向前移动相关指令启用避障
    if ((lastCommand == 'F' || lastCommand == 'L' || lastCommand == 'R') && distance < obstacleThreshold) {
      filteredCommand = 'S';
      Serial.println("🛑 避障触发 → 停止小车");
    } else {
    filteredCommand = lastCommand;
    }

    // 发送最终控制命令到下位机
   Wire.beginTransmission(8);
    Wire.write(filteredCommand);
    Wire.endTransmission();
  //}
}

// 获取距离（单位：cm）
long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 最长 30ms = 约5米
  long distance = duration * 0.034 / 2;
  return distance;
}

