#include "dp.hh"

DriversParameters::DriversParameters() { reset(); }
void DriversParameters::reset()
{
	elapsed_time = 0;
	elapsed_distance = 0;
	num_of_trips = 0;
}
void DriversParameters::addTime(int delta) { elapsed_time += delta; }
void DriversParameters::addDistance(int delta) { elapsed_distance += delta; }
void DriversParameters::addNumOfTrips() { ++num_of_trips; }
int DriversParameters::getTime() { return elapsed_time; }
int DriversParameters::getDistance() { return elapsed_distance; }
int DriversParameters::getNumOfTrips() { return num_of_trips; }