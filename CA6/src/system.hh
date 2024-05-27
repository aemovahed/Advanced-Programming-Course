#ifndef _S_HH_
#define _S_HH_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "m.hh"
#include "d.hh"
#include "drm.hh"
#include "tm.hh"
#include "dim.hh"
#include "cm.hh"
using namespace std;

enum Command {ADD_MISSION,
			  ASSIGN_MISSION, 
			  RECORD_RIDE, 
			  SHOW_MISSIONS_STATUS};
const int NUM_OF_INFO_ADD = 6;
const int NUM_OF_INFO_ASSIGN = 3;
const int NUM_OF_INFO_RECORD = 5;
const int NUM_OF_INFO_SHOW = 2; 
const int NUM_OF_CMDS = 4;
const string commands[] = {"add", "assign", "record", "show"};

class System {
public:
	void splitBySpace(string str);
	int identifyCommand();
	void addMission();
	missionPtr findMission(string mission_id);
	bool isInvalidArgument();
	bool isInvalidTimes(string start_time, string end_time);
	driverPtr findDriver(string id);
	void assignMission();
	void recordRide();
	void show_missions_status();
	void printJustCompletedMissions(vector<driversMissionPtr> missns, string driver_id);
	void printMissionsWithStatus(vector<driversMissionPtr> missns, string driver_id);
private:
	vector<string> info;
	vector<missionPtr> missions;
	vector<driverPtr> drivers;
};

#endif