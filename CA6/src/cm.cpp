#include "cm.hh"
	
bool CountMission::isJustCompleted(DriversParameters parameters)
{
	if (parameters.getNumOfTrips() >= target_parameter)
		return true;
	return false;
}
