#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class CShift {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int K; cin >> K;
        int N = S.size();
        K = min(K, N);

        vector<int> A;
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '0') { A.push_back(cnt); cnt = 0; }
            else cnt++;
        }
        A.push_back(cnt);
        reverse(A.begin(),A.end());
        int M = A.size();

        vector3<FF> DP(M+1, K+1, K+1, 0);
        DP[0][0][0] = 1;
        for (int i = 0; i < M; ++i) {
            int a = A[i];
            for (int j = 0; j <= K; ++j) {
                vector<FF> Pref(K+2, 0);
                for (int k = 0; k <= K; ++k) Pref[k+1] = Pref[k] + DP[i][j][k];

                for (int k = 0; k <= j; ++k) {
                    for (int l = 1; l <= a; ++l) {
                        if (l+j <= K) {
                            DP[i+1][j+l][k] += DP[i][j][k]; // store ones
                        }
                    }

                    DP[i+1][j][k] += Pref[k+1];
                }
            }
        }

        FF ans = 0;
        for (int i = 0; i <= K; ++i) ans += DP[M][i][i];
        cout << ans << '\n';
    }
};
