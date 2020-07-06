#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class CBeautifulMirrorsWithQueries {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> P(N); cin >> P;
        vector<FF> Prod(N+1, 1);
        for (int i = N-1; i >= 0; --i) Prod[i] = Prod[i+1] * FF{100}/P[i];
        vector<FF> Pref(N+1, 0);
        for (int i = 0; i < N; ++i) Pref[i+1] = Pref[i] + Prod[i];

        set<int> Check;
        Check.insert(0);
        Check.insert(N);
        auto calc = [&](int j, int k) {
            return (Pref[k] - Pref[j]) / Prod[k];
        };

        FF cur = calc(0, N);
        for (int i = 0; i < Q; ++i) {
            int a; cin >> a; --a;
            auto it = Check.find(a);
            if (it != Check.end()) {
                int b = *prev(it);
                int c = *next(it);
                cur -= calc(b,a);
                cur -= calc(a,c);
                cur += calc(b,c);
                Check.erase(it);
            } else {
                it = Check.lower_bound(a);
                int b = *prev(it);
                int c = *it;
                cur -= calc(b,c);
                cur += calc(b,a);
                cur += calc(a,c);
                Check.insert(a);
            }
            cout << cur << '\n';
        }
    }
};
