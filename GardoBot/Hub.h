

#include "process.h"

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

  void clearProcess() {
    for (int i = 0 ; i < MAX_PROC; ++i) {
      if ( procs[i] ) {
        procs[i]->OnEnd();
        procs[i] = NULL;
      }
    }
  }
};










