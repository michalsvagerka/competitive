#include "../l/lib.h"
// #include "../l/mod.h"

class separuj {
public:

	vector<int> dijkstra(const vector<vector<pair<int, pii>>> &E, int from) {
		minheap<pii> H;
		vector<int> R(E.size(), MOD);
		R[from] = 0;
		H.push({0,from});
		while(!H.empty()) {
			auto h = H.top(); H.pop();
			int u = h.y;
			int c = h.x;
			if (R[u] != c) continue;
			for (auto e : E[u]) {
				int v = e.x;
				int d = e.y.x;
				if (c + d < R[v]) {
					R[v] = c + d;
					H.push({R[v], v});
				}
			}
		}
		return R;
	}

    void solve(istream& cin, ostream& cout) {
		int N, M, A, B;
		cin >> N >> M >> A >> B; --A; --B;
		vector<vector<pair<int, pii>>> E(N), F(N);
		for (int i = 0; i < M; ++i) {
			int u, v, d, c; cin >> u >> v >> d >> c;
			--u; --v;
			E[u].push_back({v, {d,c}});
			F[v].push_back({u, {d,c}});
		}

		vector<int> G = dijkstra(E, A);
		vector<int> H = dijkstra(F, B);

		vector<pii> L;
		L.push_back({numeric_limits<int>::max(), 0});
		L.push_back({0, 0});
		for (int u = 0; u < N; ++u) {
			for (auto w : E[u]) {
				int v = w.x;
				int d = w.y.x;
				int c = w.y.y;
				if (G[u] < MOD && H[v] < MOD) L.push_back({d + G[u] + H[v], c});
			}
		}

		sort(L.begin(), L.end());
		for (int i = 1; i < L.size(); ++i) {
			L[i].y += L[i-1].y;
		}

		int Q; cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int p; cin >> p;
			auto it = upper_bound(L.begin(), L.end(), pii{p, numeric_limits<int>::max()});
			--it;
			cout << it->y << '\n';
		}
    }
};
