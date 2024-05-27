#ifndef _MASTER_HH_
#define _MASTER_HH_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "t.hh"
#include "p.hh"
#include "w.hh"
#include "m.hh"
using namespace std;

enum Command {POST, GET, PUT, DELETE, ERROR};
enum GetArg {team_of_the_week, 
			 players, 
			 league_standings, 
			 matches_result_league, 
			 error};

const vector<string> cmds = {"POST", "GET", "PUT", "DELETE"};
const vector<string> get_args = {"team_of_the_week", 
								 "players", 
								 "league_standings", 
								 "matches_result_league"};
const int NUM_OF_WEEKS = 19;
const int NUM_OF_PARTS_OF_PLAYERS_CMD = 5;
const int NUM_OF_PARTS_OF_WEEK_CMD = 5;

class Master {
public:
	Master();
	vector<string> splitByChar(string line, char ch);
	void readFiles();
	void readTeamsInfo();
	TeamPtr findTeam(string t);
	vector<TeamPtr> findTeams(string ts);
	PlayerPtr findPlayer(string p, vector<TeamPtr> ts);
	vector<PlayerPtr> findPlayers(vector<string> ps, vector<TeamPtr> ts);
	vector<PlayerPtr> setScoreOfPlayers(string ps, vector<TeamPtr> ts, int week_num);
	void addAMatchToTheWeek(WeekPtr week, vector<string> match_info);
	void readGamesOfWeeks();
	bool readInput();
	Command recognizeCmd();
	GetArg recognizeGetArg();
	string genNameOfTeam();
	WeekPtr findWeek(int week_num);
	WeekPtr setTeamOfTheWeek();
	void setTeamsRanking();
	void printTeamOfTheWeek(WeekPtr week);
	void printPlayers(TeamPtr team);
	void printTeams();
	void printWeekResults();
private:
	int current_week;
	vector<string> input;
	vector<TeamPtr> teams;
	vector<WeekPtr> weeks;
};

#endif