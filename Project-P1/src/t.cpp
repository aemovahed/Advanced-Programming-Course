#include "t.hh"

Team::Team(string n) 
{
	name = n;
	score = 0;
	GF = 0;
	GA = 0;
}
string Team::getName() { return name; }
int Team::getScore() { return score; }
int Team::getGD() { return GF - GA; }
int Team::getGF() { return GF; }
void Team::setPlayers(vector<vector<string>> ps)
{
	for (string gk : ps[0])
		players.push_back(make_shared<Goalkeeper>(gk));
	for (string df : ps[1])
		players.push_back(make_shared<Defender>(df));
	for (string md : ps[2])
		players.push_back(make_shared<Midfielder>(md));
	for (string fw : ps[3])
		players.push_back(make_shared<Forward>(fw));
}
PlayerPtr Team::findPlayer(string p) 
{
	for (PlayerPtr player : players)
		if (p == player->getName())
			return player;
	return NULL;
}
void Team::add(string field, int value)
{
	if (field == "score")
		score += value;
	else if (field == "GF")
		GF += value;
	else
		GA += value;
}
void Team::printPlayers(string pos)
{
	cout << "list of players:\n";
	int player_num = 1;
	for (PlayerPtr p : players)
		if (pos == "all" || pos == p->getPosition()) {
			p->printSpecs(player_num);
			++player_num;
		}
}
void Team::print()
{
	cout << name << ": score: "
		 << score << " | GF: "
		 << GF << " | GA: "
		 << GA << endl;
}