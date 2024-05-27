#ifndef _TOTW_HH_
#define _TOTW_HH

#include <memory>
#include <iostream>
#include <vector>
#include "p.hh"
using namespace std;

const int NOT_HAVING_TWO_DFS = 0;
const int NOT_HAVING_ONE_DF = 1;

class TeamOfTheWeek {
public:
	TeamOfTheWeek(int wn);
	void checkThePos(PlayerPtr p);
	void checkDfs(PlayerPtr p);
	void checkTheSoloPos(PlayerPtr& selected_player, PlayerPtr p);
	void print();
	void printSpecsOfThePlayer(PlayerPtr p);
private:
	int week_num;
	PlayerPtr gk;
	vector<PlayerPtr> dfs;
	PlayerPtr md;
	PlayerPtr fw;
};

typedef shared_ptr<TeamOfTheWeek> TOTWPtr;

#endif