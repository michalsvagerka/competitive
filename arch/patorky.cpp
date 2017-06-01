#include "../l/lib.h"
// #include "../l/mod.h"

class patorky {
public:
	int pet(ll x) {
		int ans = 0;
		while (x)  { ans += x%10==5; x/=10; }
		return ans;
	}

	void solve(istream& cin, ostream& cout) {
		ll N; int K; cin >> N >> K; ++N;
		ll p = 1;
		for (int i = 0; i < 15 && pet(N) < K; ++i, p *= 10) {
			while (N % (10*p) / p != 5 && pet(N) < K) N += p;
		}
		cout << N << endl;
	}
};
