#include "m.hh"

Mission::Mission(vector<string> info)
{
	mission_id = info[1];
	start_timestamp = stoi(info[2]);
	end_timestamp = stoi(info[3]);
	target_parameter = stoi(info[4]);
	reward_amount = info[5];
}
string Mission::getMissionID () { return mission_id; }
int Mission::getStartTimestamp() { return start_timestamp; }
int Mission::getEndTimestamp() { return end_timestamp; }
string Mission::getReward() { return reward_amount; }
void Mission::print(int end_timestamp_)
{
	cout << "start timestamp: " << start_timestamp << endl;
	cout << "end timestamp: " << end_timestamp_ << endl;
	cout << "reward: " << reward_amount << endl;
}