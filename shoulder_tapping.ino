#include <Servo.h>

#define SERVO_PIN 15

Servo servo;

void initTapShoulder() {
  servo.attach(SERVO_PIN);
}

void handleTapShoulder() {
  if (server.method() != HTTP_GET) {
    server.send(400, "text/plain", "error");
    return;
  }

  digitalWrite(LED_PIN, LOW);
  servo.write(0);
  delay(100);

  digitalWrite(LED_PIN, HIGH);
  servo.write(90);
  delay(100);

  digitalWrite(LED_PIN, LOW);
  servo.write(0);

  server.send(200, "text/plain", "success");
}


