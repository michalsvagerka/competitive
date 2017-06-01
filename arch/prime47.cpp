#include "../l/lib.h"
// #include "../l/mod.h"

class prime47 {
public:

	vector<ll> P;

	void gen(ll n, int fortyseven, int otherdigits) {
		if (!otherdigits && !fortyseven) {
			bool prime = true;
			for (ll k = 2; k*k <= n; ++k) {
				if (n % k == 0) { prime = false; break; }
			}
			if (prime) P.push_back(n);
			return;
		}


		if (otherdigits) {
			for (int i = 0; i <= 9; ++i) {
				if (i != 0 || n != 0) gen(n * 10 + i, fortyseven, otherdigits - 1);
			}
		}
		if (fortyseven) {
			gen(n * 100 + 47, fortyseven - 1, otherdigits);
		}
	}

	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;

		if (N == 1) {
			cout << "2\n3\n5\n7\n"; return;
		} else if (N == 2) {
			cout <<  "47\n"; return;
		}

		gen(0, (N-1)/2, 2-N%2);
		sort(P.begin(), P.end());
		for (ll p : P) cout << p << '\n';
	}
};
