#include "../l/lib.h"
 #include "../l/bigint.h"

class EThoroughlyBureaucraticOrganization {
public:
    vector<vector<ll>> Comb;

    ll comb(int n, int k) {
        if (n < Comb.size() && k < Comb[n].size()) return Comb[n][k];
        else {
            ll quock = 1;
            for (int j = 0; j < k; ++j) {
                if (quock >= 1e18/(n-j)) {
                    quock = 1e18;
                } else {
                    quock *= n-j;
                }
            }
            for (int j = 1; j <= k; ++j) quock /= j;
            return quock;
        }
    }

    bool canDo(int N, int M, ll req) {
        ll ones = 0;
        for (int i = 0; N > 0; ++i) {
            if (i > req) return false;
            ll quock = comb(req, i);
            if (quock > N) quock = N;
            ones += quock * i;
            N -= quock;
        }

        return req >= 1e18/M || ones <= req * M;
    }

    void solve(istream& cin, ostream& cout) {
        Comb.resize(1000);
        Comb[0] = {1};
        for (int i = 1; i < 1000; ++i) {
            Comb[i] = {1};
            for (int j = 1; j < i; ++j) {
                ll c = Comb[i-1][j-1] + Comb[i-1][j];
                Comb[i].push_back(c < 1e18 ? c : 1e18);
            }
            Comb[i].push_back(1);
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            if (N == 1) cout << "0\n";
            else cout << bsl(1, N, [&](int s) { return canDo(N, M, s); }) << '\n';
        }
    }
};
