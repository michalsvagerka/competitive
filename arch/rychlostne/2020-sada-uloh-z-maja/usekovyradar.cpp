#include "../l/lib.h"

class usekovyradar {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> V(N); cin >> V;
        vector<ll> L(N); cin >> L;

        int M; cin >> M;
        vector<pair<ll,ll>> A(M);
        for (int i = 1; i < M; ++i) cin >> A[i].x;
        for (int i = 0; i < M; ++i) cin >> A[i].y;
        A[0].x = 0;
        sort(A.begin(),A.end());
        for (int i = 1; i < M; ++i) A[i].y = max(A[i].y, A[i-1].y);

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            ll S, T; cin >> S >> T;
            T -= S;
            ll ans = 0;
            int idx = bsh(0, M-1, [&](int i) {
                double total = 0;
                for (int j = 0; j < N; ++j) {
                    total += L[j] / (double)(A[i].x + V[j]);
                }
                return total > T;
            });
            if (idx == -1) cout << "0\n";
            else cout << A[idx].y << '\n';
        }

    }
};
