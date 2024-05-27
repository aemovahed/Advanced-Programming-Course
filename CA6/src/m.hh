#ifndef _M_HH_
#define _M_HH_

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "dp.hh"
using namespace std;

class Mission {
public:
	Mission(vector<string> info);
	string getMissionID ();
	int getStartTimestamp();
	int getEndTimestamp();
	string getReward();
	virtual bool isJustCompleted(DriversParameters parameters) = 0;
	void print(int end_timestamp_);
private:
	string mission_id;
	int start_timestamp;
	int end_timestamp;
	string reward_amount;
protected:
	int target_parameter;
};

typedef shared_ptr<Mission> missionPtr;

#endif