
class MoistureSensor {
public:
  int pin;
  void init(int _pin) {
    pin = _pin;
  }
  int getValue() {
    int r = analogRead(pin);
    Serial.print("Moisture : ");
    Serial.println(((int)r)); 
    return r;
  }
};

