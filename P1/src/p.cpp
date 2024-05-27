#include "p.hh"

Player::Player(string n)
{
	name = n;
	total_score = 0;
}
string Player::getName() { return name; }
void Player::setScore(float score, int week_num)
{
	scores.push_back(make_shared<PlayerPerformance>(score, week_num));
	total_score += score;
}
string Player::getPosition() { return position; }
float Player::getScore(int week_num)
{
	for (PlayerPerformancePtr s : scores)
		if (s->getWeekNum() == week_num)
			return s->getScore();
	return -1;
}
void Player::printSpecs(int player_num)
{
	cout << player_num << ". name: " << name 
		 << " | role: " << position 
		 << " | score: " << total_score << endl;
}