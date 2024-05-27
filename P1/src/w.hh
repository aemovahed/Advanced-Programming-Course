#ifndef _W_HH_
#define _W_HH_

#include <memory>
#include <vector>
#include "m.hh"
#include "p.hh"
#include "totw.hh"
using namespace std;

class Week {
public:
	Week(int n);
	int getNum();
	void addMatch(MatchPtr match);
	void addPlayers(vector<PlayerPtr> ps);
	void setTeamOfTheWeek();
	void printTeamOfTheWeek();
	void printResults();
private:
	int number;
	TOTWPtr team_of_the_week;
	vector<MatchPtr> matches;
	vector<PlayerPtr> players;
};

typedef shared_ptr<Week> WeekPtr;

#endif