#ifndef _DP_HH_
#define _DP_HH_

class DriversParameters {
public:
	DriversParameters();
	void reset();
	void addTime(int delta);
	void addDistance(int delta);
	void addNumOfTrips();
	int getTime();
	int getDistance();
	int getNumOfTrips();
private:
	int elapsed_time;
	int elapsed_distance;
	int num_of_trips;
};

#endif