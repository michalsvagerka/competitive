#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int Z = 10008;
class primetime {
public:
    vector<vector<int>> D;
    vector<bool> P;

    unordered_map<ll, ll> M;
    int C1,C2,C3;

    ll ans(ll x) {
        C1++;
        ll cur = (x>>48)&0xffff;
        ll p23 = x&0xffffffffLL;
        if (P[cur]) {
            C3++;
            return 0x100000000LL|p23;
        }

        auto it = M.find(x);
        if (it != M.end()) return it->y;

        C2++;

        ll p1 = (x>>32)&0xffff;
        ll q = P[cur + 1] ? 0xFFFFLL : ans(((cur+1) << 48) | (p23<<16) | (min(cur + 1, p1)));
        for (int d:D[cur]) {
            ll r = ans(((cur / d) << 48) | (p23<<16) | (min(cur / d, p1)));
            if ((r&0xffff) <= (q&0xffff)) q = r;
        }

        return M[x] = ((q&0xffff)<<32)|(q>>16);
    }

    inline ll solve(int x) { return x == 1 ? 0x100010001LL : ans(x*0x1000100010001LL); }

    void solve(istream& cin, ostream& cout) {
        D.resize(Z+1);
        P.resize(Z+1);
        for (int i = 2; i <= Z; ++i) {
            P[i] = D[i].empty();
            if (D[i].empty()) {
                for (int j = i; j <= Z; j+=i) {
                    D[j].push_back(i);
                }
            }
        }

        int N; cin >> N;
        vector<int> S(3, 0);
        for (int i = 0; i < N; ++i) {
            char c; int x;
            cin >> c >> x;
            ll L = solve(x);
            ll Q0 = (L>>32)&0xffff, Q1 = (L>>16)&0xffff, Q2 = L&0xffff;
            if (c == 'O') {
                S[0] += Q0;
                S[1] += Q1;
                S[2] += Q2;
            } else if (c == 'E') {
                S[0] += Q2;
                S[1] += Q0;
                S[2] += Q1;
            } else {
                S[0] += Q1;
                S[1] += Q2;
                S[2] += Q0;
            }
        }
        cout << S;
    }
};
