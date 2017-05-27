

class LightSensor {
public:
  int pin;
  void init(int _pin) {
    pin = _pin;
  }
  int getValue() {
    int r = 1024 - analogRead(pin);
    return r;
  }
};

