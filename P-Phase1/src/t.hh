#ifndef _T_HH_
#define _T_HH_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "p.hh"
#include "df.hh"
#include "gk.hh"
#include "fw.hh"
#include "md.hh"
using namespace std;

class Team {
public:
	Team(string n);
	string getName();
	int getScore();
	int getGD();
	int getGF();
	void setPlayers(vector<vector<string>> ps);
	PlayerPtr findPlayer(string p);
	void add(string field, int value);
	void printPlayers(string pos);
	void print();
private:
	string name;
	int score;
	int GF;
	int GA;
	vector<PlayerPtr> players;
};

typedef shared_ptr<Team> TeamPtr;

#endif