#include "../l/lib.h"
#include "../l/bridges.h"
#include "../l/util.h"

class mostysem {
public:
	void solve(istream& cin, ostream& cout) {
		int N, M; cin >> N >> M;
		map<int, vector<pii>> C;
		map<pii, int> R;
		for (int i = 0; i < M; ++i) {
			int u,v,c; cin >> u >> v >> c; --u; --v;
			C[c].push_back({u,v});
			R[{u,v}] = R[{v,u}] = c;
		}
		UnionFind UF(N);
		vector<vector<int>> E(N);
		int sum = 0;
		int ans = 0;
		for (auto it = C.begin(); it != C.end(); ++it) {
			vector<pii> P;
			for (pii &e:it->y) if (!UF.united(e.x, e.y)) P.push_back(e);
			for (pii &e: P) {
				E[e.x].push_back(e.y);
				E[e.y].push_back(e.x);
				UF.unite(e.x, e.y);
			}
			if (!P.empty()) {
				Graph G(E);
				vector<pii> B;
				G.bridges(B);
				for (pii b:B)
					if (R[b] == it->x) {
						sum += it->x;
						++ans;
					}
			}
		}

		cout << ans << ' ' << sum << endl;
	}
};
