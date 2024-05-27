#include "m.hh"

Match::Match(vector<TeamPtr> ts) { teams = ts; }
void Match::setResult(vector<string> r)
{ 
	for (string num : r)
		result.push_back(stoi(num));
	for (int i = 0; i < 2; i++) {
		if (result[i] > result[1 - i])
			teams[i]->add("score", FULL_SCORE);
		if (result[i] == result[1 - i])
			teams[i]->add("score", HALF_SCORE);
		teams[i]->add("GF", result[i]);
		teams[i]->add("GA", result[1 - i]);
	}
}
void Match::setSpecialPlayers(vector<vector<PlayerPtr>> sps) 
{
	injureds = sps[0];
	yellowcards = sps[1];
	redcards = sps[2];
}
void Match::printResults()
{
	cout << teams[0]->getName() << ' ' << result[0] << " | "
		 << teams[1]->getName() << ' ' << result[1] << endl;
}