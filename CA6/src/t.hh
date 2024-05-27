#ifndef _T_HH_
#define _T_HH_

#include <vector>
#include <string>
using namespace std;

class Trip {
public:
	Trip(vector<string> info);
	int getEndTimestamp();
	int getTripDuration();
	int getTripDistance();
private:
	int start_timestamp;
	int end_timestamp;
	int distance;
};

#endif