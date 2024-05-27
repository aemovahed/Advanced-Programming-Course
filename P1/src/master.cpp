#include "master.hh"

Master::Master() { current_week = 1; }

vector<string> Master::splitByChar(string line, char ch)
{
	vector<string> fields;
	int start_pos = 0;
	while (true) {
		int char_pos = line.find(ch, start_pos);
		fields.push_back(line.substr(start_pos, char_pos - start_pos));
		if (char_pos == -1) break;
		start_pos = char_pos + 1;
	}	
	return fields;
}

void Master::readFiles() 
{
	readTeamsInfo();
	readGamesOfWeeks();
}

void Master::readTeamsInfo()
{
	ifstream file;
	file.open("premier_league.csv");
	string line;
	getline(file, line);
	while (getline(file, line)) {
		vector<string> team_info;
		team_info = splitByChar(line, ',');
		TeamPtr team = make_shared<Team>(team_info[0]);
		vector<vector<string>> players;
		for (int i = 1; i < 5; i++)
			players.push_back(splitByChar(team_info[i], ';'));
		team->setPlayers(players);
		teams.push_back(team);
	}
	file.close();
}

void Master::readGamesOfWeeks()
{
	for (int i = 0; i < NUM_OF_WEEKS; i++) {
		ifstream file;
		file.open("weeks_stats/week_" + to_string(i + 1) + ".csv");
		WeekPtr week = make_shared<Week>(i + 1);
		string line;
		getline(file, line);
		while (getline(file, line)) {
			vector<string> match_info;
			match_info = splitByChar(line, ',');
			addAMatchToTheWeek(week, match_info);
		}
		weeks.push_back(week);
		file.close();
	}
}

TeamPtr Master::findTeam(string t)
{
	for (TeamPtr team : teams)
		if (team->getName() == t)
			return team;
	return NULL;
}

vector<TeamPtr> Master::findTeams(string ts)
{
	vector<string> vec_of_teams = splitByChar(ts, ':');
	vector<TeamPtr> list_of_teams;
	for (string t : vec_of_teams) {
		TeamPtr team = findTeam(t);
		if (team != NULL)
			list_of_teams.push_back(team);
	}
	return list_of_teams;
}

PlayerPtr Master::findPlayer(string p, vector<TeamPtr> ts)
{
	for (TeamPtr t : ts) {
		PlayerPtr player;
		player = t->findPlayer(p);
		if (player != NULL)
			return player;
	}
	return NULL;
}

vector<PlayerPtr> Master::findPlayers(vector<string> ps,
									  vector<TeamPtr> ts)
{
	vector<PlayerPtr> players;
	PlayerPtr player;
	for (string p : ps) {
		player = findPlayer(p, ts);
		if (player != NULL)
			players.push_back(player);
	}
	return players;
}

vector<PlayerPtr> Master::setScoreOfPlayers(string ps, 
											vector<TeamPtr> ts, 
											int week_num)
{
	vector<PlayerPtr> players;
	vector<string> players_with_score = splitByChar(ps, ';');
	for (string p_with_s : players_with_score) {
		vector<string> p_info = splitByChar(p_with_s, ':');
		PlayerPtr p = findPlayer(p_info[0], ts);
		if (p != NULL) {
			p->setScore(stof(p_info[1]), week_num);
			players.push_back(p);
		}
	}
	return players;
}

void Master::addAMatchToTheWeek(WeekPtr week, 
								vector<string> match_info)
{
	vector<TeamPtr> ts = findTeams(match_info[0]);
	MatchPtr match = make_shared<Match>(ts);
	match->setResult(splitByChar(match_info[1], ':'));
	vector<vector<PlayerPtr>> special_players;
	for (int i = 2; i < 5; i++) {
		vector<string> players;
		players = splitByChar(match_info[i], ';');
		special_players.push_back(findPlayers(players, ts));
	}
	match->setSpecialPlayers(special_players);
	week->addPlayers(setScoreOfPlayers(match_info[5], ts, week->getNum()));
	week->addMatch(match);
}

bool Master::readInput()
{
	input.clear();
	string line;
	if (getline(cin, line)) {
		input = splitByChar(line, ' ');
		return true;
	}
	return false;
}

Command Master::recognizeCmd()
{
	for (int i = 0; i < cmds.size(); i++)
		if (input[0] == cmds[i])
			return (Command) i;
	return ERROR;
}

GetArg Master::recognizeGetArg()
{
 	for (int i = 0; i < get_args.size(); i++)
 		if (input[1] == get_args[i])
 			return (GetArg) i;
 	return error;	
}

WeekPtr Master::findWeek(int week_num)
{
	WeekPtr result = NULL;
	for (WeekPtr week : weeks)
		if (week->getNum() == week_num){
			result = week;
			break;
		}
	if (result == NULL)
		throw runtime_error("Bad Request");
	return result;
}

WeekPtr Master::setTeamOfTheWeek() 
{
	if (input.size() == NUM_OF_PARTS_OF_WEEK_CMD)
		current_week = stoi(input[4]);
	WeekPtr week = findWeek(current_week);
	week->setTeamOfTheWeek();
	return week;
}

void Master::printTeamOfTheWeek(WeekPtr week) 
{
	week->printTeamOfTheWeek();
}

string Master::genNameOfTeam() 
{
	vector<string> result = splitByChar(input[4], '_');
	string name_of_team = result[0];
	for (int i = 1; i < result.size(); i++)
		name_of_team.append(" " + result[i]);
	return name_of_team;
}

void Master::printPlayers(TeamPtr team) 
{
	if (team == NULL)
		throw runtime_error("Not Found");
	if (input.size() == NUM_OF_PARTS_OF_PLAYERS_CMD)
		team->printPlayers("all");
	if (input.size() == NUM_OF_PARTS_OF_PLAYERS_CMD + 1) {
		if (input[5] != "gk" &&
			input[5] != "df" &&
			input[5] != "md" &&
			input[5] != "fw")
			throw runtime_error("Bad Request");
		team->printPlayers(input[5]);
	}
}

void Master::setTeamsRanking()
{
	TeamPtr temp;
	for (int i = 0; i < teams.size(); i++)
		for (int j = 0; j < teams.size() - i - 1; j++) {
			if (teams[j]->getScore() > teams[j + 1]->getScore() || 
				teams[j]->getScore() == teams[j + 1]->getScore() && 
				teams[j]->getGD() > teams[j + 1]->getGD())
				continue;
			if (teams[j]->getScore() < teams[j + 1]->getScore() || 
				teams[j]->getGD() < teams[j + 1]->getGD() || 
				teams[j]->getGF() < teams[j + 1]->getGF()) 
			{
				temp = teams[j];
				teams[j] = teams[j + 1];
				teams[j + 1] = temp;
			}	
		}
}

void Master::printTeams()
{
	cout << "league standing:\n";
	for (int i = 0; i < teams.size(); i++) {
		cout << i + 1 << ". ";
		teams[i]->print();
	}
}

void Master::printWeekResults()
{
	if (input.size() == NUM_OF_PARTS_OF_WEEK_CMD)
		current_week = stoi(input[4]);
	WeekPtr week = findWeek(current_week);
	week->printResults();
}