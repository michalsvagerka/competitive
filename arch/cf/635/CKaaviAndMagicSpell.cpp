#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class CKaaviAndMagicSpell {
public:
    void solve(istream& cin, ostream& cout) {
        string S, T; cin >> S >> T;
        int N = S.size();
        int M = T.size();

        FF ans = 0;
        vector<FF> D(M+1, 0);
        for (int i = 0; i < M; ++i) if (T[i] == S[0]) D[i] = 2;
        D[M] = 2;
        if (M == 1) ans += D[0];

        for (int i = 1; i < N; ++i) {
            vector<FF> E(M+1, 0);
            for (int j = 0; j < M; ++j) {
                if (j != 0 && T[j-1] == S[i]) E[j-1] += D[j];
                int k = j+i;
                if (k >= M) E[j] += D[j];
                if (k < M && T[k] == S[i]) E[j] += D[j];
            }
            E[M] = 2*D[M];
            if (T[M-1] == S[i]) E[M-1] += D[M];

            swap(E,D);
            if (i+1 >= M) ans += D[0];
        }
        cout << ans << '\n';
    }
};
