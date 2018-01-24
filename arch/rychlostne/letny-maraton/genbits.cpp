#include "../l/lib.h"
#include "../l/primes.h"
#include "../l/random.h"

ui lg = 18;

class genbits {
public:
    void solve(istream& cin, ostream& cout) {
        LargePrimes LP;
        random_int RI(0,LP.size()-1);

        ui a,c,k,m,n;
        cin >> a >> c >> k >> m >> n;
        string s; cin >> s;
        vector2<ui> N(lg,m);
        for (int z = 0; z < m; ++z) N[0][z] = ui((((ll)a*z+c)/k)%m);
        for (int i = 1; i < lg; ++i) for (int z = 0; z < m; ++z) N[i][z] = N[i-1][N[i-1][z]];

        vector<bool> R(m,true);
        for (int t = 0; t < 1; ++t) {
            ui p = 31, f = 1000000007;//LP[RI(rng)];
            vector<ui> P(lg, p);
            for (int i = 1; i < lg; ++i) P[i] = ui((ll(P[i - 1]) * P[i - 1]) % f);

            vector2<ui> H(lg, m);
            for (int z = 0; z < m; ++z)
                H[0][z] = p * (N[0][z] >= m / 2);
            for (int i = 1; i < lg; ++i)
                for (int z = 0; z < m; ++z)
                    H[i][z] = ui(((ll) H[i - 1][z] * P[i - 1] + H[i - 1][N[i - 1][z]]) % f);

            ui h = 0;
            for (char c:s) h = ui((ll(h) * p + p * (c == '1')) % f);

            for (ui i = 0; i < m; ++i) {
                if (!R[i]) continue;
                ui z = i, r = 0;
                for (ui j = 0; j < lg; ++j) {
                    if (n & (1 << j)) {
                        r = ui((ll(r) * P[j] + H[j][z]) % f);
                        z = N[j][z];
                    }
                }
                R[i] = h == r;
            }
        }
        cout << count(R.begin(),R.end(),true) << endl;
    }
};
