#include <iostream>
using namespace std;

int combination (int n, int k) {
	if (k == n || k == 0)
		return 1;
	return combination(n - 1, k) + combination(n - 1, k - 1);
}
int main() {
	int n;
	cin >> n;
	cout << combination(2 * n, n) / (n + 1) << endl;
}