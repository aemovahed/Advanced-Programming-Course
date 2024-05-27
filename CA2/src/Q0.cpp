#include <iostream>
#include <cstring>
using namespace std;

void to_upper(string line) {
	if (line == "\0")
		return;
	if (line[0] > 96 && line[0] < 123)
		line[0] = char(int(line[0]) - 32);
	cout << line[0];
	if (line.size() > 1)
		to_upper(line.substr(1));
	return;
}
int main() {
	string line;
	while (getline(cin, line)) {
		to_upper(line);
		cout << endl;
	}
	return 0;
}