#include "../l/lib.h"
// #include "../l/mod.h"
#include "../l/util.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		int M; cin >> M;
		vector<pair<int, pii>> E(M);
		for (int i = 0; i < M; ++i) {
			cin >> E[i].y.x >> E[i].y.y >> E[i].x;
		}
		sort(E.begin(), E.end());

		int ans = MOD;
		for (int i = 0; i < (1 << (N-7)); ++i) {
			int cur = 0;
			UnionFind F(N);
			for (auto &e: E) {
				if (e.y.x >= 7 && (i & (1<<(e.y.x-7)))) continue;
				if (e.y.y >= 7 && (i & (1<<(e.y.y-7)))) continue;
				if (F.unite(e.y.x,e.y.y)) cur += e.x;
			}

			bool ok = true;
			for (int j = 0; j < 6; ++j) {
				ok &= F.united(j, 6);
			}

			if (ok) ans = min(ans, cur);
		}

		if (ans == MOD) ans = -1;
		cout << ans << endl;
    }
};
