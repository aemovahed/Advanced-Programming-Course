#include "master.hh"
using namespace std;

int main() {
	Master master;
	master.readFiles();
	while (master.readInput()) 
	{
		try {
			switch (master.recognizeCmd())
			{
			case POST:
				break;
			case GET:
				switch (master.recognizeGetArg())
				{
				case team_of_the_week:
					master.printTeamOfTheWeek(master.setTeamOfTheWeek());
					break;
				case players:
					master.printPlayers(master.findTeam(master.genNameOfTeam()));
					break;
				case league_standings:
					master.setTeamsRanking();
					master.printTeams();
					break;
				case matches_result_league:
					master.printWeekResults();
					break;
				}
				break;
			case PUT:
				break;
			case DELETE:
				break;
			}
		} catch (runtime_error& ex) {
			cout << ex.what() << endl;
		}

	}
}