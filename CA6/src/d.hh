#ifndef _D_HH_
#define _D_HH_

#include <memory>
#include <vector>
#include <string>
#include "m.hh"
#include "drm.hh"
#include "t.hh"
#include "dp.hh"

class Driver {
public:
	Driver(string id, missionPtr mission);
	string getDriverID();
	int getNumOfMissions();
	vector<driversMissionPtr> getMissions();
	void setCurrentMission(missionPtr mission);
	bool isDuplicateMission(missionPtr missn);
	void sortMissions();
	void addTrip(Trip trip);
	vector<driversMissionPtr> findJustCompletedMissions();
private:
	int trip_end_timestamp;
	string driver_id;
	DriversParameters parameters;
	driversMissionPtr current_mission;
	vector<driversMissionPtr> missions;
};

typedef shared_ptr<Driver> driverPtr;

#endif