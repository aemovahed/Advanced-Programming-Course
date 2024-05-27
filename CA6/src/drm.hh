#ifndef _DRM_HH_
#define _DRM_HH_

#include <string>
#include <memory>
#include "m.hh"
#include "dp.hh"
using namespace std;

class DriversMission {
public:
	DriversMission(missionPtr mission_);
	missionPtr getMission();
	string getMissionID();
	string getStatus();
	string getReward();
	int getStartTimestamp();
	int getEndTimestamp();
	void setEndTimestamp(int time);
	void completeStatus();
	bool isJustCompleted(DriversParameters parameters);
	void print();
private:
	missionPtr mission;
	string status;
	int end_timestamp;
};

typedef shared_ptr<DriversMission> driversMissionPtr;

#endif