#include <iostream>
#include <vector>
using namespace std;

void add1(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		v[0] += 1;
	}
}

void add2(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		v[0] += 1;
	}
}

int main() {

	vector<int> v = {1, 2, 3};
	add1(v);
	for (int i : v) {
		cout << i << " ";
	}
	cout << endl;

	add2(v);
	for (int i : v) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
