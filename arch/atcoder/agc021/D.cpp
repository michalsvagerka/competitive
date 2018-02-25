#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int K; cin >> K;
        string T = S;
        reverse(T.begin(),T.end());
        int N = S.size();
        vector3<int> L(N+1,N+1,N+3,-100000);
        for (int i = 1; i <= N; ++i) {
            L[0][i][0] = L[i][0][0] = 0;
        }
        L[0][0][0] = 0;

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (i+j>N+1) continue;
                int c = 2 - (i+j==N+1);
                for (int k = 0; k <= N; ++k) {
                    L[i][j][k] = max(L[i][j][k], L[i-1][j][k]);
                    L[i][j][k] = max(L[i][j][k], L[i][j-1][k]);
                    if (S[i-1] == T[j-1]) {
                        L[i][j][k] = max(L[i][j][k], c + L[i-1][j-1][k]);
                    } else  {
                        L[i][j][k+c] = max(L[i][j][k+c], L[i-1][j-1][k]);
                    }
                }
            }
        }


        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            int j = N-i+1;
            for (int k = 0; k <= N; ++k) {
//                cerr << L[i][j][k] << ' ' << K << ' ' << k << endl;
                int pairs = min(k,2*K);
                ans = max(ans, L[i][j][k] + pairs);
            }
        }
        cout << min(N, ans) << endl;
    }
};
