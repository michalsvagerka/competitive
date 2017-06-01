#include "../l/lib.h"
// #include "../l/mod.h"

class tapety {
public:
    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N; cin >> N;
			vector<pair<pii,pii>> P(N);
			for (int i = 0; i < N; ++i) {
				cin >> P[i].x.x >> P[i].x.y >> P[i].y.x >> P[i].y.y;
			}
			int lw = MOD, hw = 0, lh = MOD, hh = 0;
			for (int i = 0; i < N; ++i) {
				lw = min(lw, P[i].x.x);
				hw = max(hw, P[i].x.y);
				lh = min(lh, P[i].y.x);
				hh = max(hh, P[i].y.y);
			}

			bool ok = false;
			for (int i = 0; i < N; ++i) {
				ok |= (P[i].x.x == lw && P[i].x.y == hw && P[i].y.x == lh && P[i].y.y == hh);
			}
			cout << (ok ? "ANO" : "NIE") << endl;
		}
    }
};
