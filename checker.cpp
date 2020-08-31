#include<iostream>
#include<assert.h>

using namespace std;

class AlertInterface
{
public:
	virtual void raiseAlert(const char*, const char*) = 0;
};

class AlertWithSMS : public AlertInterface
{
public:
	void raiseAlert(const char* vitalName, const char* vitalLevel)
	{
		cout << "SMS : " << vitalName << " " << vitalLevel << endl;
	}
};

class AlertWithSound : public AlertInterface
{
public:
	void raiseAlert(const char* vitalName, const char* vitalLevel)
	{
		cout << "Sound : " << vitalName << " " << vitalLevel << endl;
	}
};

class AlertIntegrator : public AlertInterface
{
private:
	AlertWithSMS alertWithSMS;
	AlertWithSound alertWithSound;
public:
	void raiseAlert(const char* vitalName, const char* vitalLevel)
	{
		alertWithSMS.raiseAlert(vitalName, vitalLevel);
		alertWithSound.raiseAlert(vitalName, vitalLevel);
	}
};

class VitalRangeChecker
{
private:
	int lowerLimit;
	int upperLimit;
	const char* vitalName;

public:
	VitalRangeChecker(const char*, int, int, AlertIntegrator*);
	const char* checkVitalLevel(int);
};

VitalRangeChecker::VitalRangeChecker(const char* vitalName, int lowerLimit, int upperLimit, AlertIntegrator* alertIntegrator)
{
	this->vitalName = vitalName;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
}

const char* VitalRangeChecker::checkVitalLevel(int vitalValue)
{
	if (vitalValue < lowerLimit)
		return "TOO LOW";
	if (vitalValue > upperLimit)
		return "TOO HIGH";
	return "NORMAL";
}

class VitalsIntegrator
{
private:
	VitalRangeChecker bpmChecker, spo2Checker, respRateChecker;
	
public:
	VitalsIntegrator(AlertIntegrator* alertIntegrator) : bpmChecker("BPM", 70, 150, alertIntegrator),
		spo2Checker("BPM", 70, 150, alertIntegrator),
		respRateChecker("BPM", 70, 150, alertIntegrator)
	{ }
	void checkAllVitals(float, float, float);
};

void VitalsIntegrator::checkAllVitals(float bpm, float spo2, float respRate)
{
	bpmChecker.checkVitalLevel(bpm);
	spo2Checker.checkVitalLevel(spo2);
	respRateChecker.checkVitalLevel(respRate);
}

int main()
{
	AlertIntegrator alertIntegrator;
	VitalsIntegrator vitalsIntegrator(&alertIntegrator);

}
