

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
          if (procs[i]->attachedProcess) {
            launchProcess( procs[i]->attachedProcess);
          } 
          //deleteProcess(procs[i], true);
          procs[i] = NULL;
        }
      }
    }
  }

  void launchProcess(Process* p ) {
    if (!p) {
      return; 
    }
    for (int i = 0 ; i < MAX_PROC; ++i) {
      if ( !procs[i] ) {
        procs[i] = p;
        p->OnBegin();
        return;
      }
    }
  }

  void deleteProcess(Process* p, bool launchAttached) {
    if (!p) {
      return; 
    }
    p->OnEnd();
    if (launchAttached) {
      if (p->attachedProcess) {
        launchProcess( p->attachedProcess);
      } 
    }
    //delete (p);
  }

  void clearProcess() {
    for (int i = 0 ; i < MAX_PROC; ++i) {
      if ( procs[i] ) {
        deleteProcess(procs[i], false);
        procs[i] = NULL;
      }
    }
  }
};














