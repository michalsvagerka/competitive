#include "../l/lib.h"
#include "../l/mod.h"

class kartografie {
public:
    void solve(istream& cin, ostream& cout) {
        auto F = FieldMod::fact(1005);
        auto I = FieldMod::invfact(1005);
        vector<FieldMod> P(1005, 1);
        for (int i = 1; i < 1005; ++i) {
            P[i] = P[i-1] * 2;
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            string S; cin >> S;
            int pref = 0, suf = 0;
            while (S[pref] == '0') ++pref;
            while (S[N-1-suf] == '0') ++suf;

            FieldMod ans = I[suf] * I[pref];
            int c = suf + pref;
            int q = pref + 1;
            vector<int> L;
            while (q < N) {
                while (q < N && S[q] == '1') ++q;
                int l = q;
                while (q < N && S[q] == '0') ++q;
                if (q < N) {
                    ans *= I[q-l];
                    ans *= P[q-l-1];
                    c += q - l;
                }
            }

            ans *= F[c];
            cout << ans << '\n';
        }
    }
};
