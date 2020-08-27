#include <assert.h>

bool bpmIsOk(float bpm) {
  if(bpm < 70 || bpm > 150) {
    return false;
  }
  return true;
}

bool spo2IsOk(float spo2) {
  if(spo2 < 90) {
    return false;
  }
  return true;
}

bool respRateIsOk(float respRate) {
  if(respRate < 30 || respRate > 95) {
    return false;
  }
  return true;
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  if(bpmIsOk(bpm) && spo2IsOk(spo2) && respRateIsOk(respRate)) {
    return true;
  }
  return false;
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
