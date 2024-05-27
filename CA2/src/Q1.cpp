#include <iostream>
#include <vector>
using namespace std;

void traverse (vector<int> list_of_num, int pre_element, int max_or_min) {
	int j;
	cout << list_of_num[0] << ' ';
	if (pre_element == list_of_num[0] && pre_element == 0)
		return;
	if (max_or_min == 0)
		pre_element >= list_of_num[0] ? j = pre_element : j = list_of_num[0];
	else
		pre_element < list_of_num[0] ? j = pre_element : j = list_of_num[0];
	if (j < list_of_num.size()) {
		vector<int> temp(list_of_num.begin() + j, list_of_num.end());
		traverse(temp, list_of_num[0], !max_or_min);	
	}
	return;
}

int main() {
	int len_list, num;
	vector<int> list_of_num;
	cin >> len_list;
	while (len_list > 0) {
		cin >> num;
		list_of_num.push_back(num);
		--len_list;
	}
	traverse(list_of_num, 0, 0);
}