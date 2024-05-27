#include "d.hh"

Driver::Driver(string id, missionPtr mission)
{ 
	driver_id = id;
	setCurrentMission(mission);
}
string Driver::getDriverID() { return driver_id; }
int Driver::getNumOfMissions() { return missions.size(); }
vector<driversMissionPtr> Driver::getMissions() { return missions; }

void Driver::setCurrentMission(missionPtr mission)
{ 
	current_mission = make_shared<DriversMission>(mission);
	missions.push_back(current_mission);
	sortMissions();
	parameters.reset();
}

bool Driver::isDuplicateMission(missionPtr missn)
{ 
	for (driversMissionPtr mission : missions) 
		if (mission->getMission() == missn)
			return true;
	return false;
}

void Driver::sortMissions()
{
	driversMissionPtr temp;
	for (int i = missions.size() - 1; i > 0; i--) {
		int time = missions[i]->getStartTimestamp();
		int prev_time = missions[i - 1]->getStartTimestamp();
		if (time < prev_time) {
			temp = missions[i - 1];
			missions[i - 1] = missions[i];
			missions[i] = temp;
		}
		else break;
	}
}

void Driver::addTrip(Trip trip)
{
	parameters.addTime(trip.getTripDuration());
	parameters.addDistance(trip.getTripDistance());
	parameters.addNumOfTrips();
	trip_end_timestamp = trip.getEndTimestamp();
}

vector<driversMissionPtr> Driver::findJustCompletedMissions()
{
	vector<driversMissionPtr> just_completed_missions;
	for (driversMissionPtr mission : missions) {
		if (mission->getStatus() == "completed")
			continue;
		if (mission->isJustCompleted(parameters)) {
			mission->completeStatus();
			mission->setEndTimestamp(trip_end_timestamp);
			just_completed_missions.push_back(mission);
		}
	}
	return just_completed_missions;
}