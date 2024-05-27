#include "tm.hh"

bool TimeMission::isJustCompleted(DriversParameters parameters)
{
	if (parameters.getTime() >= target_parameter * 60)
		return true;
	return false;
}