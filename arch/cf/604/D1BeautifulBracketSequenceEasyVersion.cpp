#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class D1BeautifulBracketSequenceEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        vector<int> Q(N+1, 0);
        for (int i = 0; i < N; ++i) Q[i+1] = Q[i] + (S[i] == '?');
        vector2<FF> D(N+1, N+1, 0);
        D[N][0] = 1;
        FF ans = 0;
        vector<FF> Pow(N+1, 1);
        for (int k = 0; k < N; ++k) Pow[k+1] = Pow[k] + Pow[k];
        for (int l = N; l >= 2; --l) {
            for (int i = 0; i+l <= N; ++i) {
                int j = i+l-1;
                if (S[i] != ')' && S[j] != '(') {
                    ans += D[l][i] * Pow[Q[j]-Q[i+1]];
                    D[l-2][i+1] += D[l][i];
                }

                if (S[i] != '(') {
                    D[l-1][i+1] += D[l][i];
                }

                if (S[j] != ')') {
                    D[l-1][i] += D[l][i];
                }

                if (S[i] != '(' && S[j] != ')') {
                    D[l-2][i+1] -= D[l][i];
                }
            }
        }

        cout << ans << '\n';
    }
};
