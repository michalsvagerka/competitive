#include "../../../l/lib.h"
#include "../../../l/dinic.h"
#include <numeric>

class soldiertraveling {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M;
        cin >> N >> M;
        vector<int> A(N), B(N);
        cin >> A >> B;
        int sumA = accumulate(A.begin(),A.end(),0);
        int sumB = accumulate(B.begin(),B.end(),0);
        if (sumA != sumB) {
            cout << "NO\n";
            return;
        }

        Dinic<int> G(2*N+2);
        for (int i = 0; i < N; ++i) {
            G.AddEdge(0, i+1, A[i]);
            G.AddEdge(i+1, N+i+1, 100);
            G.AddEdge(N+i+1, 2*N+1, B[i]);
        }

        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            G.AddEdge(a, b+N, 100);
            G.AddEdge(b, a+N, 100);
        }

        if (G.GetMaxFlow(0, 2*N+1) == sumA) {
            cout << "YES\n";
            vector2<int> Ans(N,N,0);
            for (int i = 0; i < G.E; i+=2) {
                int u = G.EdgeTarget[i];
                int v = G.EdgeTarget[i+1];
                int r = G.Residual[i+1];
                if (v != 0 && u != 2*N+1) {
                    Ans[v-1][u-(N+1)] = r;
                }
            }
            for (auto&ans:Ans) cout << ans;
        } else {
            cout << "NO\n";
        }

    }
};
