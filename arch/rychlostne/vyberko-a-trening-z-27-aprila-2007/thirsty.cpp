#include "../l/lib.h"
// #include "../l/mod.h"

class thirsty {
public:
    void solve(istream& cin, ostream& cout) {
		ll W, N; cin >> W >> N;
		vector<ll> A(N); cin >> A;
		ll T = bsh(0LL, 4000000000LL, [&](ll t) {
			ll w = 0;
			for (ll a: A) {
				w += (t+a)/(a+1) * a;
			}
			return w <= W;
		});

		vector<ll> R(N, 0);
		for (int i = 0; i < N; ++i) {
			ll w = (T + A[i]) / (A[i] + 1) * A[i];
			R[i] = w;
			W -= w;
		}

		for (int i = 0; i < N; ++i) {
			if (T % (A[i]+1) == 0) {
				ll w = min(W, A[i]);
				R[i] += w;
				W -= w;
			}
		}

		int best = 0;
		ll amount = R[0];
		for (int i = 1; i < N; ++i) {
			if (R[i] > amount) {
				amount = R[i];
				best = i;
			}
		}

		cout << best << endl;
    }
};
