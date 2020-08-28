#include<assert.h>
#include<iostream>

using namespace std;

class Alert
{
  public:
    virtual void raiseAlert(const char*, const char*) = 0;
};

class AlertWithSMS: public Alert
{
  public:
    void raiseAlert(const char* vitalName, const char* level)
    {
      cout<<"SMS : "<<vitalName<<" "<<level<<endl;
    }
};

class AlertWithSound: public Alert
{
  public:
    void raiseAlert(const char* vitalName, const char* level)
    {
      cout<<"Sound : "<<vitalName<<" "<<level<<endl;
    }
};

class VitalsChecker
{
  public:
    const char* vitalIsInLimits(int vitalValue, int lowerLimit, int upperLimit) {
      if(vitalValue < lowerLimit)
        return "TOO LOW";
      if(vitalValue > upperLimit)
        return "TOO HIGH";
      return "NORMAL";
    }
    void vitalsAreOk(float bpm, float spo2, float respRate) {
      const char* bpmLevel = vitalIsInLimits(bpm, 70, 150);
      const char* spo2Level = vitalIsInLimits(spo2, 90, 100);
      const char* respRateLevel = vitalIsInLimits(respRate, 30, 95);
      
      Alert* alert;
      AlertWithSMS alertWithSMS;
      AlertWithSound alertWithSound;
      
      alert = &alertWithSMS;
      alert->raiseAlert("BPM", bpmLevel);
      alert->raiseAlert("SPO2", spo2Level);
      alert->raiseAlert("Resp Rate", respRateLevel);
      
      alert = &alertWithSound;
      alert->raiseAlert("BPM", bpmLevel);
      alert->raiseAlert("SPO2", spo2Level);
      alert->raiseAlert("Resp Rate", respRateLevel);
    }
};

int main() {
  /*assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
  assert(vitalIsInLimits(90, 70, 150) == true);
  assert(vitalIsInLimits(80, 90, 100) == false);
  assert(vitalIsInLimits(98, 30, 95) == false);*/
  VitalsChecker vitalsChecker;
  vitalsChecker.vitalsAreOk(80, 95, 60);
  vitalsChecker.vitalsAreOk(60, 90, 40);
  vitalsChecker.vitalsAreOk(80, 90, 100);
}
