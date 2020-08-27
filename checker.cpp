#include <assert.h>

/*bool bpmIsOk(float bpm) {
  return (bpm >= 70 && bpm <= 150);
}

bool spo2IsOk(float spo2) {
  return (spo2 >= 90);
}

bool respRateIsOk(float respRate) {
  return (respRate >= 30 && respRate <= 95);
}*/

bool vitalIsInLimits(int vitalValue, int lowerLimit, int upperLimit) {
  return(vitalValue >= lowerLimit && vitalValue <= upperLimit);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (vitalIsInLimits(bpm, 70, 150) && vitalIsInLimits(spo2, 90, 100) && vitalIsInLimits(respRate, 30, 95));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
