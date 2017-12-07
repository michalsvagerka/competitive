#include "../l/lib.h"
// #include "../l/mod.h"

class miniplanar {
public:
	bool hask33(const vector<set<int>> &E, int i, int A, int B, vector<int> &C) {
		if (i == 6) {
			int e = 0;
			for (int u = 0; u < 6; ++u) {
				for (int v : E[u]) {
					e += (C[u] != C[v]);
				}
			}
			return e == 9;
		} else {
			if (A < 3) {
				C[i] = 0;
				if (hask33(E, i + 1, A+1, B, C)) return true;
			}
			if (B < 3) {
				C[i] = 1;
				if (hask33(E, i + 1, A, B+1, C)) return true;
			}
		}

		return false;
	}

	bool isplanar(const vector<set<int>> &E) {
		int N = E.size();
		int M = 0;
		for (int i = 0; i < N; ++i) M += E[i].size();
		if (M < 9 || N <= 5) return M < 10;
		if (N == 6) {
			if (M > 12) return false;

			vector<int> C(6);
			if (hask33(E, 0, 0, 0, C)) return false;
		}
		if (N == 7 && M > 15) return false;

		for (int u = 0; u < N; ++u) {
			for (int v : E[u]) {
				vector<set<int>> R(N-1);
				for (int a = 0; a < N; ++a) {
					for (int b : E[a]) {
						int s = a;
						if (s == v) s = u;
						if (s > v) --s;
						if (b == v) b = u;
						if (b > v) --b;
						if (s == b) continue;
						if (s > b) swap(s,b);
						R[s].insert(b);
					}
				}

				if (!isplanar(R)) return false;

			}
		}

		return true;

	}

    void solve(istream& cin, ostream& cout) {
		int N, M; cin >> N >> M;

		vector<set<int>> E(N);
		for (int i = 0; i < M; ++i) {
			int u, v; cin >> u >> v;
			if (u > v) swap(v, u);
			E[u].insert(v);
		}

		if (isplanar(E)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
    }
};
