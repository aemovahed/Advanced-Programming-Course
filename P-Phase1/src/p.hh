#ifndef _P_HH_
#define _P_HH_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "pp.hh"
using namespace std;

class Player {
public:
	Player(string n);
	string getName();
	void setScore(float score, int week_num);
	string getPosition();
	float getScore(int week_num);
	void printSpecs(int player_num);
protected:
	string position;
private:
	string name;
	vector<PlayerPerformancePtr> scores;
	float total_score;
};

typedef shared_ptr<Player> PlayerPtr;

#endif