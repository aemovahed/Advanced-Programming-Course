#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

int max_matrix_element(int num_of_mem, int matrix[][2], vector<string> date) {
	int temp[2];
	for (int i = 0; i < num_of_mem - 1; ++i)
		for (int j = 0; j < num_of_mem - i - 1; ++j)
			if (matrix[j][1] > matrix[j + 1][1]) {
				temp[0] = matrix[j][0];
				temp[1] = matrix[j][1];
				matrix[j][0] = matrix[j + 1][0];
				matrix[j][1] = matrix[j + 1][1];
				matrix[j + 1][0] = temp[0];
				matrix[j + 1][1] = temp[1];
			}
	int desired_index = num_of_mem - 1; 
	for (int i = num_of_mem - 2; i >= 0; --i)
		if (matrix[desired_index][1] == matrix[i][1])
			if (date[matrix[desired_index][0]].compare(date[matrix[i][0]]) > 0)
				desired_index = i;
	return matrix[desired_index][0];
}

int find_day(string str, vector<string> date) {
	for (int i = 0; i < date.size(); ++i)
		if(!str.compare(date[i]))
			return i;
	return -1;
}

int recognize_command(string str) {
	string list_of_commands[4] = {"start_day", "show_day", "show_the_longest_day", "show_the_best_day"};
	for (int i = 0; i < 4; ++i) {
		int command_size = list_of_commands[i].size();
		int result_of_comparison = list_of_commands[i].compare(str.substr(0, command_size));
		if (!result_of_comparison)
			return i + 1;
	}
	return 0; 	
}

vector<string> file_to_vector() {
	string str;
	vector<string> pos_words_vec;
	ifstream pos_words_file;
	pos_words_file.open("../asset/positive-words.txt");
	while (getline(pos_words_file, str))
		pos_words_vec.push_back(str);
	pos_words_file.close();
	return pos_words_vec;
}

int find_the_string(string first_str, string second_str, int mode_num) {
	int num_of_word = 0, position = 0;
	if (mode_num == 3) {
		second_str.insert(0, 1, ' ');
		second_str.append(" ");
		while ((position = first_str.find(second_str, position)) != string::npos) {
			position += second_str.size();
			++num_of_word;
		}
	}
	else {
		if (mode_num == 1)
			second_str.append(" ");
		else
			second_str.insert(0, 1, ' ');
		position = first_str.find(second_str);
		if(position == 0)
			++num_of_word;
	}
	return num_of_word;
}

vector<int> NumOfWords(vector<string> memories, vector<string> pos_words) {
	vector<int> sum_of_num(memories.size());
	for (int i = 0; i < memories.size(); ++i)
		for (int j = 0; j < pos_words.size(); ++j) {
			int num_of_word;
			num_of_word = find_the_string(memories[i], pos_words[j], 1);
			num_of_word += find_the_string(memories[i], pos_words[j], 2);
			num_of_word += find_the_string(memories[i], pos_words[j], 3);
			sum_of_num[i] += num_of_word;
		}
	return sum_of_num;
}

void print_summary(vector<string> memories, vector<string> date, int desired_day) {
	cout << date[desired_day] << endl;
	if (memories[desired_day].size() > 20)
		cout << memories[desired_day].substr(0, 20) << "..." << endl;
	else
		cout << memories[desired_day];
}

int main() {
	string str;
	vector<string> date, memories;
	while (getline(cin, str)) {
		int desired_day;
		int result_of_comparison = recognize_command(str);
		int matrix[memories.size()][2];
		vector<int> num_of_pos_words;
		vector<string> pos_words;
		switch (result_of_comparison) {
		case 1 :
			date.push_back(str.substr(10, 9));
			getline(cin, str);
			memories.push_back(str);
			break;
		case 2 :
			desired_day = find_day(str.substr(9, 14), date);
			cout << memories[desired_day] << endl;
			break;
		case 3 :
			for (int i = 0; i < memories.size(); ++i) {
				matrix[i][0] = i;
				matrix[i][1] = memories[i].size();
			}
			desired_day = max_matrix_element(memories.size(), matrix, date);
			print_summary(memories, date, desired_day);
			break;
		case 4 :
			pos_words = file_to_vector();
			num_of_pos_words = NumOfWords(memories, pos_words);
			for (int i = 0; i < memories.size(); ++i) {
				matrix[i][0] = i;
				matrix[i][1] = num_of_pos_words[i];
			}
			desired_day = max_matrix_element(memories.size(), matrix, date);
			print_summary(memories, date, desired_day);
			break;
		default :
			int index = memories.size() - 1;
			memories[index].append("\n");
			memories[index].append(str);
		}
	}
}