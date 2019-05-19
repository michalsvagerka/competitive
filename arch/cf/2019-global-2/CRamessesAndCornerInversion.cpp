#include "../l/lib.h"

class CRamessesAndCornerInversion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M), B(N, M);
        cin >> A >> B;
        vector<int> R(N, 0), C(M, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                R[i] += A[i][j] != B[i][j];
                C[j] += A[i][j] != B[i][j];
            }
        }
        
        for (int i = 0; i < N; ++i) {
            if (R[i] % 2 == 1) {
                cout << "No\n";
                return;
            }
        }


        for (int j = 0; j < M; ++j) {
            if (C[j] % 2 == 1) {
                cout << "No\n";
                return;
            }
        }
        
        cout << "Yes\n";
    }
};
