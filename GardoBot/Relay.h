

class Relay {
public:
  int relayPin;
  void init(int _relay) {
    relayPin = _relay;
    pinMode(relayPin, OUTPUT);
  }
  void turnOn() {
    digitalWrite(relayPin, HIGH);
  }
  void turnOff() {
    digitalWrite(relayPin, LOW);
  }
};

