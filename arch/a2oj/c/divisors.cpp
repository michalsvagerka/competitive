#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int LIM = 1e5;

class divisors {
public:
    ll X,K;
    map<ll,vector<ll>> Divs;
    vector<ll> Ans;

    vector<ll> divs(ll X) {
        vector<ll> l,h;
        for (ll i = 1; i*i <= X; ++i) {
            if (X%i == 0) {
                l.push_back(i);
                if (i*i!=X) h.push_back(X/i);
            }
        }
        reverse(h.begin(),h.end());
        l.insert(l.end(),h.begin(),h.end());
        return l;
    }

    void put(ll Y, ll M) {
        if (Ans.size() == LIM) return;

        if (Y == 1 || M == 0) {
            Ans.push_back(Y);
        } else {
            for (ll d: Divs[Y]) {
                put(d, M-1);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> X >> K;
        Divs[X] = divs(X);
        for (ll d:Divs[X]) {
            if (d != X) {
                for (ll w:Divs[X]) {
                    if (d % w == 0) {
                        Divs[d].push_back(w);
                    }
                }
            }
        }
        put(X, K);
        cout << Ans;
    }
};
