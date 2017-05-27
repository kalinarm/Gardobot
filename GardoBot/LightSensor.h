

class LightSensor {
public:
  int pin;
  void init(int _pin) {
    pin = _pin;
  }
  int getValue() {
    int r = (int)((1024 - analogRead(pin))*100.0/1024.0);
    return r;
  }
};

