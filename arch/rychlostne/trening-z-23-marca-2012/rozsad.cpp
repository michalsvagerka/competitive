#include "../l/lib.h"
#include "../l/hungary.h"

class rozsad {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> B(N, {-1,-1});
        for (int i = 0; i < 2*N; ++i) {
            int a; cin >> a; --a;
            B[a].x = B[a].y;
            B[a].y = i;
        }

        vector2<int> C(N,N,0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                C[i][j] = abs(B[i].x - j) + abs(B[i].y - (j+N));
            }
        }
        Hungary<int> H(C);
        H.minCost();
        vector<int> A(2*N);
        for (int i = 0; i < N; ++i) A[i] = A[N+i] = H.yx[i] + 1;
        cout << A;
    }
};
