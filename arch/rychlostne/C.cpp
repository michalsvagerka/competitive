#include "../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<ll> V(N);
		vector<ll> D(N-1);
		cin >> V >> D;

		for (int i = 1; i < N-1; ++i) {
			D[i] += D[i-1];
		}

		for (int i = 1; i < N; ++i) {
			V[i] += D[i-1];
		}

		ll reach = V[0];
		ll dist = 0;
		int d = 0;
		int ans = 0;
		while (d < N-1) {
			ll best = 0;
			while (d < N-1 && D[d] < reach) { best = max(best, V[d+1]); ++d; ++ans; }
			--ans;
			reach = best;
		}
		cout << ans << endl;
    }
};
