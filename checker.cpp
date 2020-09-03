#include<iostream>
#include<vector>
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
	vector<VitalRangeChecker> vitalDetails;

public:
	VitalsIntegrator(AlertInterface* alertPtr)
	{
		vitalDetails.push_back(VitalRangeChecker("bpm", 70, 150, alertPtr));
		vitalDetails.push_back(VitalRangeChecker("spo2", 90, 100, alertPtr));
		vitalDetails.push_back(VitalRangeChecker("respRate", 30, 95, alertPtr));
	}
	void checkAllVitals(const vector<float>);
};

void VitalsIntegrator::checkAllVitals(vector<float> vitalValuesToCheck)
{
	for (int i = 0; i < vitalDetails.size(); i++)
	{
		vitalDetails[i].checkVitalLevel(vitalValuesToCheck[i]);
	}
}

int main()
{
	AlertIntegrator alerter;
	VitalsIntegrator vitals(&alerter);
	vitals.checkAllVitals({ 85, 98, 88 });
	vitals.checkAllVitals({ 65, 92, 97 });
	return 0;
}
