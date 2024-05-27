#include "system.hh"
 
int main() {
	System system;
	string str;
	while (getline(cin, str))
	{
		system.splitBySpace(str);
		try {
			switch ((Command) system.identifyCommand())
			{
			case ADD_MISSION :
				system.addMission();
				break;
			case ASSIGN_MISSION :
				system.assignMission();
				break;
			case RECORD_RIDE :
				system.recordRide();
				break;
			case SHOW_MISSIONS_STATUS :
				system.show_missions_status();
				break;
			}
		} catch (runtime_error& ex) {
			cout << ex.what() << endl;
		}
	}
}