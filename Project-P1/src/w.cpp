#include "w.hh"

Week::Week(int n) 
{
	number = n;
	team_of_the_week = make_shared<TeamOfTheWeek>(number);
}
int Week::getNum() { return number; }
void Week::addMatch(MatchPtr match) { matches.push_back(match); }
void Week::addPlayers(vector<PlayerPtr> ps) { players = ps; }
void Week::setTeamOfTheWeek() 
{
	for (PlayerPtr p : players)
		team_of_the_week->checkThePos(p); 
}
void Week::printTeamOfTheWeek() {
	team_of_the_week->print();
}
void Week::printResults() {
	for (MatchPtr match : matches)
		match->printResults();
}