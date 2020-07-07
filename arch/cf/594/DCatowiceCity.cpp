#include "../../../l/lib.h"
#include "../../../l/graph.h"

class DCatowiceCity {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            DirectedGraph D(N);
            for (int i = 0; i < M; ++i) {
                int a, b; cin >> a >> b;
                --a; --b;
                if (a != b) D.addEdge(a, b);
            }
            D.calcStronglyConnectedComponents();
            vector<int> U;
            for (int v: D.stronglyConnectedPermutation()) {
                if (U.empty() || D.stronglyConnected(v, U.back())) U.push_back(v);
            }
            if (U.size() == N) {
                cout << "No\n";
            } else {
                vector<bool> Q(N, false);
                for (int u: U) Q[u] = true;
                vector<int> A, B;
                for (int i = 0; i < N; ++i) {
                    (Q[i]?A:B).push_back(i+1);
                }

                cout << "Yes\n" << A.size() << ' ' << B.size() << '\n' << A << B;
            }
        }
    }
};
