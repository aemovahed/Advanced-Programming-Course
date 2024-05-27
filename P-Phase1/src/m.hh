#ifndef _M_HH_
#define _M_HH_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "t.hh"
#include "p.hh"
using namespace std;

const int FULL_SCORE = 3;
const int HALF_SCORE = 1;

class Match {
public:
	Match(vector<TeamPtr> ts);
	void setResult(vector<string> r);
	void setSpecialPlayers(vector<vector<PlayerPtr>> sps);
	void printResults();
private:
	vector<TeamPtr> teams;
	vector<int> result;
	vector<PlayerPtr> injureds;
	vector<PlayerPtr> yellowcards;
	vector<PlayerPtr> redcards;
};

typedef shared_ptr<Match> MatchPtr;

#endif