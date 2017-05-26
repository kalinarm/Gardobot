

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
  void setRed(float value) {
    analogWrite(redpin, value);
  }
   void setGreen(float value) {
    analogWrite(greenpin, value);
  }
   void setBlue(float value) {
    analogWrite(bluepin, value);
  }

  void turnOff() {
    setColor(0,0,0);
  }
};

