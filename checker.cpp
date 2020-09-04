#include<iostream>
#include<map>
#include<string>
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
	void raiseAlert(const char* vitalName, const char* vitalLevel) override
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
	AlertInterface* alerter;

public:
	VitalRangeChecker() {}
	VitalRangeChecker(const char*, int, int, AlertInterface*);
	void checkVitalLevel(float);
};

VitalRangeChecker::VitalRangeChecker(const char* vitalName, int lowerLimit, int upperLimit, AlertInterface* alerter)
{
	this->vitalName = vitalName;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
	this->alerter = alerter;
}

void VitalRangeChecker::checkVitalLevel(float vitalValue)
{
	if (vitalValue < lowerLimit)
		alerter->raiseAlert(vitalName, "TOO LOW");
	else if (vitalValue > upperLimit)
		alerter->raiseAlert(vitalName, "TOO HIGH");
	else
		alerter->raiseAlert(vitalName, "OK");
}

class VitalsIntegrator
{
private:
	map<string, VitalRangeChecker> vitalDetails;

public:
	VitalsIntegrator(AlertInterface* alertPtr)
	{
		vitalDetails["bpm"] = VitalRangeChecker("bpm", 70, 150, alertPtr);
		vitalDetails["spo2"] = VitalRangeChecker("spo2", 90, 100, alertPtr);
		vitalDetails["respRate"] = VitalRangeChecker("respRate", 30, 95, alertPtr);
	}
	void checkAllVitals(const map<string, float>& );
};

void VitalsIntegrator::checkAllVitals(const map<string, float> &vitalValuesToCheck)
{
	map<string, float>::const_iterator itr = vitalValuesToCheck.begin();
	while (itr != vitalValuesToCheck.end())
	{
		vitalDetails[itr->first].checkVitalLevel(itr->second);
		itr++;
	}
}

int main()
{
	AlertIntegrator alerter;
	VitalsIntegrator vitals(&alerter);
	vitals.checkAllVitals({ {"bpm", 78},{"spo2", 95}, {"respRate", 90} });
	vitals.checkAllVitals({ {"bpm", 65},{"spo2", 98}, {"respRate", 97} });
	return 0;
}
