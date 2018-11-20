#include "../l/lib.h"
// #include "../l/mod.h"

class ESegmentsOnTheLine {
public:
void solve(istream& cin, ostream& cout) {
    int N, S, M, K; cin >> N >> S >> M >> K;
    vector<int> A(N); cin >> A;
    vector<pii> I(S); cin >> I;
    for (auto&i: I) { --i.x; --i.y; }
    vector<int> X(N, -1);
    for (int i = 0; i < N; ++i) {
        for (auto j:I) {
            if (j.x <= i && j.y >= i) X[i] = max(X[i], j.y);
        }
    }

    vector<int> G = A;
    sort(G.begin(),G.end());

    vector2<int> D(N+1, M+1, -1);
    int s = bsl(0, N-1, [&](int j) {
        int thr = G[j];
        vector<int> P(N+1, 0);
        for (int i = 0; i < N; ++i) {
            P[i+1] = P[i] + (A[i] <= thr);
        }
        D[0][0] = 0;

        for (int i = 1; i <= N; ++i) {
            for (int s = 0; s <= M; ++s) {
                D[i][s] = -1;
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int s = 0; s <= M; ++s) {
                D[i+1][s] = max(D[i+1][s], D[i][s]);
                int e = X[i];
                if (e != -1 && s != M) {
                    D[e+1][s+1] = max(D[e+1][s+1], D[i][s] + P[e+1] - P[i]);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= M; ++i) {
            ans = max(ans, D[N][i]);
        }
        return ans >= K;
    });

    if (s == -1) cout << -1 << endl;
    else cout << G[s] << endl;
}
};
