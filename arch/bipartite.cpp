#include "../l/lib.h"
// #include "../l/mod.h"

class bipartite {
public:
    void solve(istream& cin, ostream& cout) {
		int N, M; cin >> N >> M;
		vector<vector<int>> E(N);
		for (int i = 0; i < M; ++i) {
			int u,v; cin >> u >> v; --u; --v;
			E[u].push_back(v); E[v].push_back(u);
		}

		vector<pii> R;
		vector<bool> P(N, false);
		for (int i = 1; i < N; ++i) {
			vector<int> A,B;
			for (int u:E[i]) {
				if (u<i) {
					(P[u]?A:B).push_back(u);
				}
			}
			if (A.size() > B.size()) {
				P[i] = false;
				for (int b:B) R.push_back({b+1,i+1});
			} else {
				P[i] = true;
				for (int a:A) R.push_back({a+1,i+1});
			}
		}
		cout << R.size() << '\n';
		for(pii&r: R) cout << r.x << ' ' << r.y << '\n';
    }
};
