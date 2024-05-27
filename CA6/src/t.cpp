#include "t.hh"

Trip::Trip(vector<string> info)
{
	start_timestamp = stoi(info[1]);
	end_timestamp =  stoi(info[2]);
	distance = stoi(info[4]);
}
int Trip::getEndTimestamp() { return end_timestamp; }
int Trip::getTripDuration() { return end_timestamp - start_timestamp; }
int Trip::getTripDistance() { return distance; }