#ifndef _PP_HH_
#define _PP_HH_

#include <memory>
using namespace std;

class PlayerPerformance {
public:
	PlayerPerformance(float s, int wn);
	int getWeekNum();
	float getScore();
private:
	float score;
	int week_num;
};

typedef shared_ptr<PlayerPerformance> PlayerPerformancePtr;

#endif