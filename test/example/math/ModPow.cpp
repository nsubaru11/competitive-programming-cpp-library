#include <iostream>

#include "lib/math/ModPow.hpp"

using namespace std;

int main() {
	long long m, n, mod = 1000000007;
	cin >> m >> n;
	cout << mod_pow(m, n, mod) << endl;
	return 0;
}
