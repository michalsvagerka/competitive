#include "../l/lib.h"
#include "../l/primes.h"

class DAnticube {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<ll> S(N); cin >> S;
    auto P = Sieve{2200}.primes();
    auto R = Sieve{ui(1e5)}.primes();
    map<ll, ll> Sqrt;
    for (int r: R) Sqrt[ll(r)*r] = r;

    vector<ll> PC;
    for (int p: P) PC.push_back(ll(p)*p*ll(p));

    map<ll, int> T;
    for (ll s : S) {
        for (ll p : PC) while (s % p == 0) s /= p;
        T[s]++;
    }

    set<pair<ll,ll>> W;
    int ans = 0;
    for (auto t: T) {
        ll a = t.x, o = 1;
        if (a == 1) { ans++; continue; }

        for (int p : P) {

            if (a % p == 0) {
                a /= p;
                o *= p;
                if (a % p == 0) {
                    a /= p;
                } else {
                    o *= p;
                }
                if (o > 1e11) o = 1e11;

            }
        }

        if (Sqrt[a]) {
            o *= Sqrt[a];
        } else {
            if (a <= 1e5) { o *= a; o *= a; }
            else o = 1e11;
        }

        W.insert({min(o,t.x),max(o,t.x)});
    }

    for (auto w: W) ans += max(T[w.x], T[w.y]);

    cout << ans << endl;
}
};
