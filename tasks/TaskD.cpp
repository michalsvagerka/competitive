#include "../l/lib.h"
#include "../l/dinic.h"
#include "../l/flow.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
		ui T; cin >> T;
		ui res = 0;
		for (int t = 0; t < T; ++t) {
			ui N = 1500;
			Dinic<int> X(N);
			PushRelabel<int> Y(N);
			for (int i = 0; i < N*N/10; ++i) {
				ui u = rand() % N;
				ui v = rand() % N;
				int c = 10 + rand() % 1000;
				if (u != v) {
					X.AddEdge(u, v, c);
					Y.AddEdge(u, v, c);
				}
			}
			res += X.GetMaxFlow(2, N-1);
			res -= Y.GetMaxFlow(2, N-1);
		}
		cout << res << endl;
    }
};
