#include "../l/lib.h"
// #include "../l/mod.h"

class DXeniaAndBitOperations {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> S(N+1);
        for (int i = 0; i <= N; ++i) {
            S[i].resize(1<<i);
        }
        cin >> S[N];
        for (int i = N-1; i >= 0; --i) {
            for (int j = 0; j < 1<<i; ++j) {
                if ((N-i)%2==0) {
                    S[i][j] = S[i+1][2*j] ^ S[i+1][2*j+1];
                } else {
                    S[i][j] = S[i+1][2*j] | S[i+1][2*j+1];
                }
            }
        }

        for (int i = 0; i < M; ++i) {
            int p, b; cin >> p >> b;
            --p;
            S[N][p] = b;
            for (int j = N-1; j >= 0; --j) {
                p /= 2;
                if ((N-j)%2==0) {
                    S[j][p] = S[j+1][2*p] ^ S[j+1][2*p+1];
                } else {
                    S[j][p] = S[j+1][2*p] | S[j+1][2*p+1];
                }
            }
            cout << S[0][0] << '\n';
        }

    }
};
