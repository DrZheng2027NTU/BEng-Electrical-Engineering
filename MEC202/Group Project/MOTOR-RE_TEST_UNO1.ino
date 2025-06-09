#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command = 'S';
char currentCommand = 'S';
unsigned long lastCommandTime = 0;
const unsigned long timeout = 500;  // 命令有效期

void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void loop() {
  unsigned long now = millis();

  // 若超时未更新命令 → 自动停止
  if ((now - lastCommandTime > timeout) && currentCommand != 'S') {
    currentCommand = 'S';
    Serial.println("🛑 超时无新命令，执行停止");
    executeCommand(currentCommand);
  }

  // 若 command 与 currentCommand 不一致（说明刚收到或刚切换）→ 执行新命令
  if (command != currentCommand) {
    currentCommand = command;
    executeCommand(currentCommand);
    Serial.print("⚙️ 执行命令: ");
    Serial.println(currentCommand);
  }

  delay(20);  // 可选：减少处理延迟
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    command = Wire.read();
    lastCommandTime = millis();  // 每次接收都刷新时间
    Serial.print("📩 收到命令: ");
    Serial.println(command);
  }
}

void executeCommand(char cmd) {
  int fast = 200;
  int slow = 100;

  switch (cmd) {
    case 'F':
      setAllMotors(fast, FORWARD);
      break;
    case 'B':
      setAllMotors(fast, BACKWARD);
      break;
    case 'L':
      motor1.setSpeed(fast); motor1.run(FORWARD);
      motor2.setSpeed(slow); motor2.run(FORWARD);
      motor3.setSpeed(slow); motor3.run(FORWARD);
      motor4.setSpeed(fast); motor4.run(FORWARD);
      break;
    case 'R':
      motor1.setSpeed(slow); motor1.run(FORWARD);
      motor2.setSpeed(fast); motor2.run(FORWARD);
      motor3.setSpeed(fast); motor3.run(FORWARD);
      motor4.setSpeed(slow); motor4.run(FORWARD);
      break;
    default:
      stopAllMotors();
      break;
  }
}

void setAllMotors(int speed, int dir) {
  motor1.setSpeed(speed); motor1.run(dir);
  motor2.setSpeed(speed); motor2.run(dir);
  motor3.setSpeed(speed); motor3.run(dir);
  motor4.setSpeed(speed); motor4.run(dir);
}

void stopAllMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

