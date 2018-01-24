#include "../l/lib.h"

class commuting {
public:
	void solve(istream& cin, ostream& cout) {
		int N; 
		cin >> N;
		vector<int> F(N);
		cin >> F;
		for (int &f: F) --f;
		vector<int> G(N, -1);
		vector<vector<int>> C(N+1);
		for (int i = 0; i < N; ++i) {
			if (G[i] != -1) continue;
			vector<int> P{i};
			for (int v = F[i]; v != i; v = F[v]) P.push_back(v);
			int l = P.size();
			for (int j = l; j >= 1; --j) if (!C[j].empty() && l % j == 0) {
					for (int k = 0; k < l; ++k) G[P[k]] = C[j][k % j];
					break;
				}
			if (G[i] == -1) {
				C[l] = P;
 				for (int k = 0; k < l; ++k) G[P[k]] = C[l][k];
			}
		}

		for (int i = 0; i < N; ++i) {
			assert(F[G[i]] == G[F[i]]);
		}

		for (int &g: G) ++g;
		cout << G;
	}
};
