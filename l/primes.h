#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <algorithm>

struct Sieve : public std::vector<bool> {
	explicit Sieve(int n) : vector<bool>(n+1, true), n(n) {
		for (int i = 2; i*i <= n; ++i) {
			if (at(i)) for (int j = i*i; j <= n; j+=i) (*this)[j] = false;
		}
	}

	vector<int> primes() const {
		vector<int> ans;
		for (int i=2; i<=n; ++i) if (at(i)) ans.push_back(i);
		return ans;
	}

private:
	int n;
};

struct Moebius : public std::vector<std::pair<int, int>> {
	explicit Moebius(int n) : Moebius(n, Sieve{n}.primes()) {}

	Moebius(int n, const vector<int>& primes) {
		search(-1, 1, 1, n, primes);
		std::sort(begin(), end());
	}
private:
	void search(int i, int x, int y, int n, const vector<int>&primes) {
		push_back({x,y});
		while (++i < primes.size() && (ll)x * primes[i] <= n) search(i, x*primes[i], -y, n, primes);
	}
};

#endif //PRIMES_H
