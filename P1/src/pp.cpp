#include "pp.hh"

PlayerPerformance::PlayerPerformance(float s, int wn)
{
	score = s;
	week_num = wn;
}
int PlayerPerformance::getWeekNum() { return week_num; }
float PlayerPerformance::getScore() { return score; }