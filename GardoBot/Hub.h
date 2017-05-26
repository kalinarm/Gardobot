

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

int MAX_PROC = 5;

class Hub {
public : 

  Process** procs;


  void init() {
    procs = new Process*[MAX_PROC];
    for (int i = 0 ; i < MAX_PROC; ++i) {
      procs[i] = NULL;
    }
    // start working...
    Serial.println("=================================");
    Serial.println("GardoBot Init");
  }

  void doStep(float dt) {
    for (int i = 0 ; i < MAX_PROC; ++i) {
      if ( procs[i] ) {
        procs[i]->OnStep(dt); 
        if (procs[i]->isFinish()) {
          procs[i]->OnEnd();
          procs[i] = NULL;
        }
      }
    }
  }

  void launchProcess(Process* p ) {
    for (int i = 0 ; i < MAX_PROC; ++i) {
      if ( !procs[i] ) {
        procs[i] = p;
        p->OnBegin();
        return;
      }
    }
  }




};









