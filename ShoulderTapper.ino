class ShoulderTapper
{
private:
  static const int left_1 =  5;
  static const int left_2 = 16;
  static const int left_3 =  4;

  static const int right_1 = 12;
  static const int right_2 = 13;
  static const int right_3 = 14;

public:
  ShoulderTapper();
  void tap(const int power);
};

ShoulderTapper::ShoulderTapper()
{
  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);
}

void ShoulderTapper::tap(const int power)
{
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);
  analogWrite(left_3, power);

  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);
  analogWrite(right_3, power);
}
