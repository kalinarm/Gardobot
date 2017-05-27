

class Process {
public :
  float timeSinceStart;
  float duration;
  Process* attachedProcess;

  Process(float _duration) {
    duration = _duration * 1000.0;
    timeSinceStart = 0;
    attachedProcess = NULL;
  }
  virtual void OnBegin() {

  } 
  virtual void OnEnd() {

  } 
  virtual void OnStep(float dt) {
    timeSinceStart += dt;
    /*Serial.print(timeSinceStart);
     Serial.print(" / ");
     Serial.println(duration);*/
  }
  virtual bool isFinish() {
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


class ProcessFade : 
public Process {
public :
  int repetition;
  ProcessFade(float _duration) : 
  Process(_duration) {
    repetition = 0;
  }
  ProcessFade(float _duration, int _repetition) : 
  Process(_duration) {
    repetition = _repetition - 1;
  }
  virtual void OnBegin() {
    rgb.setColor(0, 0, 0);
  } 
  virtual void OnEnd() {
    rgb.setColor(0, 0, 0);
  } 

  virtual void OnStep(float dt) {
    timeSinceStart += dt;
    float factor = (timeSinceStart / duration);
    if (factor > 0.5) {
      factor = 1.0 - factor; 
    }
    rgb.setColor(factor * 255, 0, 0);
  }
  virtual bool isFinish() {
    if ( timeSinceStart >= duration) {
      if (repetition > 0) {
        repetition-=1;
        timeSinceStart = 0;
      }
      else {
        return true; 
      }
    }
    return false;
  }
};


class ProcessMonitor : 
public Process {
public :

  float lightAccum;

  ProcessMonitor() : 
  Process(0) {
    duration = 86400;
  }
  virtual void OnBegin() {
    lightAccum = 0;
    Serial.println("--> start monitoring");

  } 
  virtual void OnEnd() {
    Serial.println("<-- stop monitoring");
  } 
  virtual void OnStep(float dt) {
    timeSinceStart += dt;
    lightAccum += lightVal;
  }

  virtual bool isFinish() {
    return timeSinceStart >= duration;
  }
};







