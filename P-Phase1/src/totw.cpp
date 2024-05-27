#include "totw.hh"

TeamOfTheWeek::TeamOfTheWeek(int wn)
{
	week_num = wn;
	gk = NULL;
	md = NULL;
	fw = NULL;
}

void TeamOfTheWeek::checkThePos(PlayerPtr p)
{
	if (p->getPosition() == "df")
		checkDfs(p);
	else {
		if (p->getPosition() == "gk")
			checkTheSoloPos(gk, p);
		if (p->getPosition() == "md")
			checkTheSoloPos(md, p);
		if (p->getPosition() == "fw")
			checkTheSoloPos(fw, p);
	}
}

void TeamOfTheWeek::checkDfs(PlayerPtr p) 
{
	if (dfs.size() == NOT_HAVING_TWO_DFS)
		dfs.push_back(p);
	else if (dfs.size() == NOT_HAVING_ONE_DF) {
		if (p->getScore(week_num) > dfs[0]->getScore(week_num)) {
			dfs.push_back(dfs[0]);
			dfs[0] = p;
		}
		else
			dfs.push_back(p);
	}
	else if (p->getScore(week_num) > dfs[0]->getScore(week_num)) {
		dfs[1] = dfs[0];
		dfs[0] = p;
	}
	else if (p->getScore(week_num) > dfs[1]->getScore(week_num))
		dfs[1] = p;
}

void TeamOfTheWeek::checkTheSoloPos(PlayerPtr& selected_player, PlayerPtr p)
{
	if (selected_player == NULL)
		selected_player = p;
	else if	(p->getScore(week_num) > selected_player->getScore(week_num)) 
		selected_player = p;
		
}

void TeamOfTheWeek::print()
{
	cout << "team of the week:\n";
	cout << "GoalKeeper: ";
	printSpecsOfThePlayer(gk);
	cout << "Defender 1: ";
	printSpecsOfThePlayer(dfs[0]);
	cout << "Defender 2: ";
	printSpecsOfThePlayer(dfs[1]);
	cout << "Midfielder: ";;
	printSpecsOfThePlayer(md);
	cout << "Forward: ";
	printSpecsOfThePlayer(fw);
}

void TeamOfTheWeek::printSpecsOfThePlayer(PlayerPtr p)
{
	cout << p->getName() << " | score: " << p->getScore(week_num) << '\n';
}