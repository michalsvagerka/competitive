#include "../l/lib.h"
#include "../l/primes.h"

class mnammnam {
public:
	void solve(istream& cin, ostream& cout) {
		Moebius MB(1000000);
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int M, N; cin >> N >> M;
			if (N > M) swap(N, M);
			ll ans = (N > 0) + (M > 0);
			for(const pii&mb: MB) {
				if (mb.x > N) break;
				ans += (ll)(N / mb.x) * (M / mb.x) * mb.y;
			}
			cout << ans << endl;
		}
	}
};
