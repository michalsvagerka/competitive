#include "../l/lib.h"
// #include "../l/mod.h"

class kamion {
public:
    void solve(istream& cin, ostream& cout) {
		int N,Z;cin>>N>>Z;
		vector2<int> E(N,N,-1);
		for (int i = 0; i < Z; ++i) {
			int a,b,c; cin >> a >> b >> c;
			--a; --b;
			E[a][b] = max(E[a][b],c);
		}
		vector<vector<pii>> F(N);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (E[i][j] >= 0) F[i].push_back({j,E[i][j]});
			}
		}

		double best = 0.0;
		for (int i = 0; i < N; ++i) {
			vector2<int> B(N+1,N,-MOD);
			B[0][i] = 0;
			for (int j = 0; j < N; ++j) {
				for (int k = 0; k < N; ++k) {
					if (B[j][k] < 0) continue;
					for (pii&p: F[k]) {
						B[j+1][p.x] = max(B[j+1][p.x], B[j][k] + p.y);
					}
				}

				best = max(best, ((double)B[j+1][i]) / (j+1));
			}
		}
		cout << fixed << setprecision(16) << best << endl;
    }
};
