#include <iostream>
#include <limits>

using namespace std;

int high_value(initializer_list<int> vals) {
	int high = numeric_limits<int>::lowest();
	if (vals.size() == 0) return high;
	for (auto x : vals) {
		if (x > high) high = x;
	}
	return high;
}

int main() {
	cout << high_value({}) << "\n";
	cout << high_value({ 1, 2, 0 }) << "\n";
}