#include "../l/lib.h"
#include "../l/flow.h"

class schedule {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> S(N);
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            S[i].resize(x); cin >> S[i];
        }

        PushRelabel<int> R(N+M+2);
        for (int i = 0; i < N; ++i) {
            R.AddEdge(0, i+1, 1);
            for (auto s:S[i]) {
                R.AddEdge(i + 1, s + N, 1);
            }
        }
        for (int i = 1; i <= M; ++i) {
            R.AddEdge(N+i, N+M+1, 1);
        }
        int top = R.GetMaxFlow(0, N+M+1);
        if (top < N) {
            cout << "NO " << top << '\n';
            return;
        }

        cout << "YES " << bsh(0, M, [&](int c) {
            if (c==0) return true;

            PushRelabel<int> R(N+M+2);
            for (int i = 0; i < N; ++i) {
                R.AddEdge(0, i+1, c);
                for (auto s:S[i]) {
                    R.AddEdge(i + 1, s + N, 1);
                }
            }
            for (int i = 1; i <= M; ++i) {
                R.AddEdge(N+i, N+M+1, 1);
            }

            return R.GetMaxFlow(0,N+M+1) == c*N;
        }) << '\n';
    }
};
