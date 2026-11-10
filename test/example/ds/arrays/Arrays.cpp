#include <iostream>

#include "lib/ds/arrays/Arrays.hpp"

using namespace std;

int main() {
	int n = 0;
	int q = 0;
	cin >> n;
	cin >> q;
	Arrays<int> arr(n);
	arr.set_all([](int i) { return i + 1; });
	while (q-- > 0) {
		int t = 0;
		cin >> t;
		if (t == 1) {
			int p = 0;
			int x = 0;
			cin >> p;
			cin >> x;
			arr[p - 1] = x;
		} else if (t == 2) {
			int p = 0;
			cin >> p;
			cout << arr[p - 1] << endl;
		} else {
			int k = 0;
			cin >> k;
			k %= n;
			arr.rotate_left(k);
		}
	}
	return 0;
}
