#include "../l/lib.h"
// #include "../l/mod.h"
#include "../l/graph.h"

class TALCA {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		Tree<1> T(N);
		for (int i = 0; i < N-1; ++i) {
			int u,v; cin >> u >> v;
			T.addEdge(u, v);
		}
		int Q; cin >> Q;
		for (int i = 0; i < Q; ++i) {
			int r, u, v; cin >> r >> u >> v;
			int l1 = T.lca(u,v), l2 = T.lca(r,u), l3 = T.lca(r,v);
			if (l2 == l3) cout << l1;
			else if (l1 == l3) cout << l2;
			else cout << l3;
			cout << endl;
		}
	}
};
