#include "../l/lib.h"
#include "../l/flow.h"

struct floe {
	int x, y, n, m;
};

class penguins {
public:
	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N; double D; cin >> N >> D;
			D *= D;
			vector<floe> F(N);
			int png = 0;
			for (floe&f:F) {
				cin >> f.x >> f.y >> f.n >> f.m;
				png += f.n;
			}

			vector<int> A;
			for (int i = 0; i < N; ++i) {
				PushRelabel<int> G(2*N+2);
				for (int j = 0; j < N; ++j) {
					for (int k = 0; k < N; ++k) {
						if ((F[j].x - F[k].x) * (F[j].x - F[k].x) + (F[j].y - F[k].y) * (F[j].y - F[k].y) <= D) {
							G.AddEdge(2*j+1, 2*k, png);
						}
					}
					G.AddEdge(2*j, 2*j+1, F[j].m);
					G.AddEdge(2*N, 2*j, F[j].n);
				}
				G.AddEdge(2*i, 2*N+1, png);
				if (G.GetMaxFlow(2*N, 2*N+1) == png) {
					A.push_back(i);
				}
			}
			if (A.empty()) cout << "-1\n";
			else cout << A;
		}
	}
};
