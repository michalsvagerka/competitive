#include "../l/lib.h"
// #include "../l/mod.h"

class eldorado {
public:
	void solve(istream& cin, ostream& cout) {
		int N, K; cin >> N >> K;

		while (N && K) {
			vector<int> A(N); cin >> A;
			vector2<ll> D(N, K, 0);
			ll ans = 0;
			for (int i = 0; i < N; ++i) {
				D[i][0] = 1;
				for (int p = 0; p < i; ++p) {
					if (A[p] < A[i]) {
						for (int k = 1; k < K; ++k) {
							if (!D[p][k-1]) continue;
							D[i][k] += D[p][k-1];
						}
					}
				}
				ans += D[i][K-1];
			}
			cout << ans << '\n';

			cin >> N >> K;
		}
	}
};
