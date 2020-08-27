#include <assert.h>

bool bpmIsOk(float bpm) {
  return (bpm >= 70 && bpm <= 150);
}

bool spo2IsOk(float spo2) {
  return (spo2 >= 90);
}

bool respRateIsOk(float respRate) {
  return (respRate >= 30 && respRate <= 95);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (bpmIsOk(bpm) && spo2IsOk(spo2) && respRateIsOk(respRate));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
