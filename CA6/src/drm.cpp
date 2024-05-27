#include "drm.hh"

DriversMission::DriversMission(missionPtr mission_)
{
	mission = mission_;
	status = "ongoing";
	end_timestamp = -1;
}
missionPtr DriversMission::getMission() { return mission; }
string DriversMission::getMissionID() { return mission->getMissionID(); }
string DriversMission::getStatus() { return status; }
string DriversMission::getReward() { return mission->getReward(); }
int DriversMission::getStartTimestamp() { return mission->getStartTimestamp(); }
int DriversMission::getEndTimestamp() { return end_timestamp; }
void DriversMission::setEndTimestamp(int time) { end_timestamp = time; }
void DriversMission::completeStatus() { status = "completed"; }
bool DriversMission::isJustCompleted(DriversParameters parameters)
{ 
	return mission->isJustCompleted(parameters);
}
void DriversMission::print() { mission->print(end_timestamp); }