#include "../l/lib.h"
// #include "../l/mod.h"
#include "../l/graph.h"

class bachelors {
public:
	void solve(istream& cin, ostream& cout) {
		int M, F; cin >> M >> F;
		Bipartite<1> G(M, F);
		int N; cin >> N;
		for (int i = 0; i < N; ++i) {
			int a,b; cin >> a >> b;
			if (a > M) swap(a,b);
			if (a > M || b <= M) continue;
			G.addEdge(a, b);
		}
		vector<int> I = G.indep();
		vector<int> C = G.cover();
		I.push_back(0);
		cout << I.size() << endl << I;
		cout << C.size() << endl << C;
	}
};
