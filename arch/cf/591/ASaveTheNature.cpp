#include "../../../l/lib.h"

class ASaveTheNature {
public:
    void solve(istream& cin, ostream& cout) {
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int N; cin >> N;
            vector<int> P(N); cin >> P;
            for (int i = 0; i < N; ++i) {
                P[i] /= 100;
            }

            int X, A, Y, B; cin >> X >> A >> Y >> B;
            ll K; cin >> K;
            vector<pii> C(N);
            for (int i = 0; i < N; ++i) {
                int x = 0;
                if ((i+1)%A == 0) x += X;
                if ((i+1)%B == 0) x += Y;
                C[i] = {x, i};
            }
            sort(C.begin(),C.end());
            sort(P.begin(),P.end());
            reverse(C.begin(),C.end());
            reverse(P.begin(),P.end());
            int ans = bsl(0, N, [&](int q) {
                ll tot = 0;
                int j = 0;
                for (int i = 0; i < N; ++i) {
                    if (C[i].y < q) tot += P[j++] * C[i].x;
                }
                return tot >= K;
            });
            cout << ans << endl;
        }
    }
};
