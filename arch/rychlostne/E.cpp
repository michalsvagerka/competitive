#include "../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
		int Q; cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int N; cin >> N;
			vector<pair<pii, pii>> X(N);
			for (int i = 0; i < N; ++i) {
				int A,B,T; cin >> A >> B >> T;
				X[i] = {{A+B, T}, {A,B}};
			}
			sort(X.begin(), X.end());
			int prev = 0;
			bool ok = true;
			for (auto& x : X) {
				int beg = max(prev, x.y.x);
				int end = beg + x.x.y;
				if (end > x.y.y) { ok = false; break; }
				prev = end;
			}

			cout << (ok ? "ANO" : "NIE") << endl;
		}
    }
};
