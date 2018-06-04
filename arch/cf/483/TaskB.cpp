#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;

        vector2<int> B(N,N+1,0);
        for (int i = 0; i < N; ++i) {
            B[i][i+1] = A[i];
        }


        for (int i = N-1; i >= 0; --i) {
            for (int j = i+2; j <= N; ++j) {
                B[i][j] = B[i][j-1] ^ B[i+1][j];
            }
        }


        for (int i = N-1; i >= 0; --i) {
            for (int j = i+1; j <= N; ++j) {
                if (i != 0) {
                    B[i-1][j] = max(B[i-1][j], B[i][j]);
                }
                if (j != N) {
                    B[i][j+1] = max(B[i][j+1], B[i][j]);
                }
            }
        }

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int l,r; cin >> l >> r;
            cout << B[l-1][r] << '\n';
        }
    }
};
