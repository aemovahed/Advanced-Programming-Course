#ifndef _DIM_HH_
#define _DIM_HH_

#include "m.hh"
#include "dp.hh"

class DistanceMission : public Mission {
public:
	DistanceMission(vector<string> info) : Mission(info) {}
	bool isJustCompleted(DriversParameters parameters);
};

#endif