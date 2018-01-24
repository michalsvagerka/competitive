#include "../l/lib.h"
// #include "../l/mod.h"

class mostyprec {
public:
	int N;
	vector<vector<pii>> E;
	vector<bool> L;

	pii dfs(int u, int ig) {
		pii ans = {0, u};
		for(pii p: E[u]) {
			int v = p.x;
			if (v != ig && !L[v]) {
				pii ret = dfs(v, u);
				ret.x += p.y;
				ans = max(ret, ans);
			}
		}
		return ans;
	}

    void solve(istream& cin, ostream& cout) {
		cin >> N;
		while (N) {
			E.clear(); E.resize(N);
			vector<int> P(N-1), C(N-1); cin >> P >> C;
			int ans = 0;
			for (int i = 0; i < N-1; ++i) {
				E[i+1].push_back({P[i]-1,C[i]});
				E[P[i]-1].push_back({i+1,C[i]});
				ans += 3*C[i];
			}
			L.resize(N);
			int nonLeaf = -1;
			for (int i = 0; i < N; ++i) {
				L[i] = E[i].size() == 1;
				if (L[i]) ans -= 2*E[i][0].y; else nonLeaf = i;
			}

			pii one = dfs(nonLeaf, -1);
			pii two = dfs(one.y, -1);
			ans -= two.x;

			cout << ans << '\n';

			cin >> N;
		}
    }
};
