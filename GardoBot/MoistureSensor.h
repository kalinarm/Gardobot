
class MoistureSensor {
public:
  int pin;
  void init(int _pin) {
    pin = _pin;
  }
  int getValue() {
    int r = analogRead(pin);
    return r;
  }
};

