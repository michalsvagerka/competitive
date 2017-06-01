#include "../l/lib.h"
// #include "../l/mod.h"

class charizma {
public:
	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		int N; cin >> N;
		vector<vector<pii>> I(T);
		for (int i = 0; i < N; ++i) {
			int c,b,t; cin >> c >> b >> t;
			I[t-1].push_back({c,b});
		}
		int P; cin >> P;
		vector2<int> B(T, P+1, 0);
		for (pii &p: I[0]) if (p.x <= P) B[0][p.x] = max(B[0][p.x], p.y);
		for (int t = 1; t < T; ++t) {
			for (int i = 0; i <= P; ++i) {
				if (B[t-1][i]) {
					for (pii &p: I[t]) {
						if (i + p.x <= P) B[t][p.x+i] = max(B[t][p.x+i], p.y + B[t-1][i]);
					}
				}
 			}
		}

		cout << *max_element(B[T-1].begin(), B[T-1].end()) << endl;
	}
};
