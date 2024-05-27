#include "system.hh"

void System::splitBySpace(string str)
{
	info.clear();
	int start_pos = 0;
	while (start_pos < str.size()) {
		int space_pos = str.find(' ', start_pos);
		if (space_pos == string::npos) {
			info.push_back(str.substr(start_pos));
			break;
		}
		info.push_back(str.substr(start_pos, space_pos - start_pos));
		start_pos = space_pos + 1;
	}
}

int System::identifyCommand()
{
	for (int i = 0; i < NUM_OF_CMDS; i++)
		if (info[0].find(commands[i]) != string::npos)
			return i;
	return -1;
}

void System::addMission()
{
	if (info.size() != NUM_OF_INFO_ADD)
		throw runtime_error("INVALID_ARGUMENTS");
	if (findMission(info[1]))
		throw runtime_error("DUPLICATE_MISSION_ID");
	if (isInvalidArgument())
		throw runtime_error("INVALID_ARGUMENTS");
	if (info[0] == "add_time_mission")
		missions.push_back(make_shared<TimeMission>(info));
	else if (info[0] == "add_distance_mission")
		missions.push_back(make_shared<DistanceMission>(info));
	else if (info[0] == "add_count_mission")
		missions.push_back(make_shared<CountMission>(info));
	cout << "OK" << endl;
}

missionPtr System::findMission(string mission_id)
{
	for (missionPtr mission : missions)
		if (mission->getMissionID() == mission_id)
			return mission;
	return NULL;
}

bool System::isInvalidArgument()
{
	if (isInvalidTimes(info[2], info[3]))
		return true;
	if (info[4].find('-') != string::npos || info[5].find('-') != string::npos)
		return true;
	return false;
}

bool System::isInvalidTimes(string start_time, string end_time)
{
	if (stoi(start_time) > stoi(end_time))
		return true;
	return false;
}

driverPtr System::findDriver(string id)
{
	for (driverPtr driver : drivers)
		if (driver->getDriverID() == id)
			return driver;
	return NULL;
}

void System::assignMission()
{
	if (info.size() != NUM_OF_INFO_ASSIGN)
		throw runtime_error("INVALID_ARGUMENTS");
	missionPtr mission = findMission(info[1]);
	if (mission == NULL)
		throw runtime_error("MISSION_NOT_FOUND");
	driverPtr driver = findDriver(info[2]);
	if (driver == NULL)
		drivers.push_back(make_shared<Driver>(info[2], mission));
	else {
		if (driver->isDuplicateMission(mission))
			throw runtime_error("DUPLICATE_DRIVER_MISSION");
		driver->setCurrentMission(mission);
	}
	cout << "OK" << endl;
}

void System::recordRide()
{
	if (info.size() != NUM_OF_INFO_RECORD)
		throw runtime_error("INVALID_ARGUMENTS");
	if (isInvalidTimes(info[1], info[2]))
		throw runtime_error("INVALID_ARGUMENTS");
	driverPtr driver = findDriver(info[3]);
	if (driver == NULL)
		throw runtime_error("INVALID_ARGUMENTS");
	if (!driver->getNumOfMissions())
		return;
	driver->addTrip(Trip(info));
	printJustCompletedMissions(driver->findJustCompletedMissions(), info[3]);
}

void System::show_missions_status()
{
	if (info.size() != NUM_OF_INFO_SHOW)
		throw runtime_error("INVALID_ARGUMENTS");
	driverPtr driver = findDriver(info[1]);
	if (driver == NULL)
		throw runtime_error("MISSION_NOT_FOUND");
	if (!driver->getMissions().size())
		throw runtime_error("DRIVER_MISSION_NOT_FOUND");
	printMissionsWithStatus(driver->getMissions(), info[1]);
}

void System::printJustCompletedMissions(vector<driversMissionPtr> missns, string driver_id)
{
	cout << "completed missions for driver " << driver_id << ":" << endl;
	for (int i = 0; i < missns.size(); i++) {
		cout << "mission: " << missns[i]->getMissionID() << endl;
		missns[i]->print();
		if (i != missns.size() - 1)
			cout << endl;
	}
}

void System::printMissionsWithStatus(vector<driversMissionPtr> missns, string driver_id)
{
	cout << "missions status for driver " << driver_id << ":" << endl;
	for (int i = 0; i < missns.size(); i++) {
		cout << "mission " << missns[i]->getMissionID() << ":" << endl;
		missns[i]->print();
		cout << "status: " << missns[i]->getStatus() << endl;
		if (i != missns.size() - 1)
			cout << endl;
	}
}