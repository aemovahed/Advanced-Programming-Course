#include "dim.hh"

bool DistanceMission::isJustCompleted(DriversParameters parameters)
{
	if (parameters.getDistance() >= target_parameter)
		return true;
	return false;
}