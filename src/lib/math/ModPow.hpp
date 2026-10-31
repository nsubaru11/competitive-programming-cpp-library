#pragma once

/** base^exp mod m を繰り返し二乗法で求める。 */
inline long long modPow(long long base, long long exp, const long long mod) {
	long long ans = 1;
	for (; exp; base = base * base % mod, exp >>= 1) {
		if (exp & 1)
			ans = ans * base % mod;
	}
	return ans;
}
