ShoulderTapper shoulderTapper;

void handleTapShoulder() {
  if (server.method() != HTTP_GET) {
    server.send(400, "text/plain", "error");
    return;
  }

  String power = server.arg("power");

  if (power == "0") {
    shoulderTapper.tap(0);
    server.send(200, "text/plain", "success");
  } else if (power == "1") {
    shoulderTapper.tap(256);
    server.send(200, "text/plain", "success");
  } else if (power == "2") {
    shoulderTapper.tap(512);
    server.send(200, "text/plain", "success");
  } else if (power == "3") {
    shoulderTapper.tap(1024);
    server.send(200, "text/plain", "success");
  } else {
    server.send(400, "text/plain", "invalid parameter");
    return;
  }
}


Led rightLed(1);
Led leftLed(2);

void handleRightShoulderLed()
{
  rightLed.blink();
  server.send(200, "text/plain", "success");
}

void handleLeftShoulderLed()
{
  leftLed.blink();
  String power = server.arg("power");
  return;
}
