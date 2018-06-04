#include "../../../l/lib.h"
// #include "../l/mod.h"

class yetanotherproblemwithqueens {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> P(M); cin >> P;
        vector<int> T(M, 0);
        for (int dx = 0; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy != 1) continue;
                vector<pii> L(3*N+1, {N+1,N+1}), H(3*N+1, {0,0});
                for (int i = 0; i < M; ++i) {
                    int s = P[i].x*dx+P[i].y*dy+N;
                    L[s] = min(L[s], P[i]);
                    H[s] = max(H[s], P[i]);
                }

                for (int i = 0; i < M; ++i) {
                    int s = P[i].x*dx+P[i].y*dy+N;
                    if (L[s] != P[i]) T[i]++;
                    if (H[s] != P[i]) T[i]++;
                }
            }
        }


        vector<int> A(9,0);
        for (int&t:T) A[t]++;
        cout << A;
    }
};
