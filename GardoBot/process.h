

class Process {
public :
  float timeSinceStart;
  float duration;
  Process(float _duration) {
    duration = _duration * 1000.0;
    timeSinceStart = 0;
  }
  virtual void OnBegin() {

  } 
  virtual void OnEnd() {

  } 
  virtual void OnStep(float dt) {
    timeSinceStart += dt;
    Serial.print(timeSinceStart);
    Serial.print(" / ");
    Serial.println(duration);
  }
  bool isFinish() {
    return timeSinceStart >= duration;
  }
};


class ProcessRelay : 
public Process {
public :
  Relay relay;
  ProcessRelay(Relay _relay, float _duration) : 
  Process(_duration) {
    relay = _relay;
  }
  virtual void OnBegin() {
    Serial.println("--> start relay");
    relay.turnOn();
  } 
  virtual void OnEnd() {
    Serial.println("<-- stop relay");
    relay.turnOff();
  } 
};

class ProcessWater : 
public Process {
public :
  ProcessWater(float _duration) : 
  Process(_duration) {

  }
  virtual void OnBegin() {
    Serial.println("--> start watering");
    rgb.setBlue(255);
    relayWater.turnOn();
  } 
  virtual void OnEnd() {
    Serial.println("<-- stop watering");
    relayWater.turnOff();
    rgb.setBlue(0);
  } 
};

class ProcessLight : 
public Process {
public :
  ProcessLight(float _duration) : 
  Process(_duration) {

  }
  virtual void OnBegin() {
    Serial.println("--> start lighting");
    rgb.setRed(255);
    rgb.setGreen(255);
    relayLight.turnOn();
  } 
  virtual void OnEnd() {
    Serial.println("<-- stop lighting");
    rgb.setRed(0);
    rgb.setGreen(0);
    relayLight.turnOff();
  } 
};

