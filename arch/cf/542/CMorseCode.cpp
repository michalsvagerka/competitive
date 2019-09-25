#include "../l/lib.h"
#include "../l/mod.h"

class CMorseCode {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector2<FieldMod> D(N, N+1, 0);
        for (int i = 0; i < N; ++i) {
            D[i][i] = 1;
            for (int j = i+1; j <= N; ++j) {
                if (j-i >= 1) D[i][j] = D[i][j-1];
                if (j-i >= 2) D[i][j] += D[i][j-2];
                if (j-i >= 3) D[i][j] += D[i][j-3];
                if (j-i >= 4) {
                    int mask = A[j-1]|A[j-2]<<1|A[j-3]<<2|A[j-4]<<3;
                    if (mask != 3 && mask != 5 && mask != 14 && mask != 15) {
                        D[i][j] += D[i][j-4];
                    }
                }
            }
        }
        
        vector2<int> L(N+1, N+1, 0);
        for (int i = N-1; i >= 0; --i) {
            for (int j = i-1; j >= 0; --j) {
                if (A[i] == A[j]) L[i][j] = 1 + L[i+1][j+1];
            }
        }

        for (int i = 0; i < N; ++i) {
            int len = 0;
            for (int j = 0; j < i; ++j) len = max(len, L[i][j]);
            for (int j = 0; j <= len; ++j) D[i][i+j] = 0;
        }
        

        vector<FieldMod> S(N+1, 0);
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j < N; ++j) {
                S[i] += D[j][i];
            }
        }
        
        for (int i = 0; i < N; ++i) S[i+1] += S[i];
        for (int i = 1; i <= N; ++i) cout << S[i] << '\n';
    }
};
