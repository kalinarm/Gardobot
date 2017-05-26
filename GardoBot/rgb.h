

class RGB {
public:
  void init() {
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
    turnOff();
  }
  void setColor(float red, float green, float blue) {
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
  } 

  void turnOff() {
    setColor(0,0,0);
  }
};

