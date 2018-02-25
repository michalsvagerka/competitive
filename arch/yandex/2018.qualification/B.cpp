#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> Q(2*N, N); cin >> Q;
        vector<int> TL(N*N+1, 0);
        for (int i = 0; i < 2 * N; ++i) {
            TL[Q[i][0]]++;
        }

        int topLeft = 0;
        for (int i = 1; i <= N*N; ++i) {
            if (TL[i] == 2) {
                topLeft = i;
                
                break;
            }
        }

        vector<int> A(N*N);
        for (int i = 0; i < 2*N; ++i) {
            if (Q[i][0] == topLeft) {
                for (int j = 0; j < N; ++j) {
                    A[j*N] = Q[i][j];
                }
                Q[i][0] = -1;
                break;
            }
        }

        for (int i = 0; i < 2*N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[j*N] == Q[i][0]) {
                    for (int k = 0; k < N; ++k) {
                        A[j*N+k] = Q[i][k];
                    }
                }
            }
        }

        cout << A;
    }
};
