class Led
{
private:
  int pin;

public:
  Led(const int pin) :pin(pin) {
    pinMode(pin, OUTPUT);
  }

  void blink();
};

void Led::blink()
{
  digitalWrite(pin, HIGH);
  delay(100);

  digitalWrite(pin, LOW);
}
