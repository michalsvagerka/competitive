#include "../l/lib.h"
#include "../l/subset.h"

class ELittleCLoves3III {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string AS, BS; cin >> AS >> BS;
        vector<ll> AR(1<<N), BR(1<<N);
        for (int i = 0; i < 1<<N; ++i) {
            int p = __builtin_popcount(i);
            AR[i] = ll(AS[i]-'0')<<(2*p);
            BR[i] = ll(BS[i]-'0')<<(2*p);
        }

        zetaTransform(AR, N);
        zetaTransform(BR, N);
        vector<ll> CR(1<<N);
        for (int i = 0; i < 1<<N; ++i) CR[i] = AR[i] * BR[i];
        moebiusTransform(CR, N);
        string C(1<<N, '?');
        for (int i = 0; i < 1<<N; ++i) {
            int p = __builtin_popcount(i);
            C[i] = char('0'+((CR[i]>>(2*p))&3));
        }

        cout << C << '\n';
    }
};
