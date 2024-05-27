#ifndef _TM_HH_
#define _TM_HH_

#include "m.hh"
#include "dp.hh"

class TimeMission : public Mission {
public:
	TimeMission(vector<string> info) : Mission(info) {}
	bool isJustCompleted(DriversParameters parameters);
};

#endif