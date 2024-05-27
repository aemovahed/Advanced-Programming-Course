#ifndef _CM_HH_
#define _CM_HH_

#include "m.hh"
#include "dp.hh"

class CountMission : public Mission {
public:
	CountMission(vector<string> info) : Mission(info) {}
	bool isJustCompleted(DriversParameters parameters);
};

#endif