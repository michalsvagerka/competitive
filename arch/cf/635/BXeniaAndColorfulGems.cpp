#include "../l/lib.h"

class BXeniaAndColorfulGems {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int NR, NG, NB; cin >> NR >> NG >> NB;
            set<int> R,G,B;
            for (int i = 0; i < NR; ++i) {
                int a; cin >> a; R.insert(a);
            }
            for (int i = 0; i < NG; ++i) {
                int a; cin >> a; G.insert(a);
            }
            for (int i = 0; i < NB; ++i) {
                int a; cin >> a; B.insert(a);
            }

            ll ans = 3e18;
            auto test = [&](ll a, ll b, ll c) {
                ll x = a-b;
                ll y = a-c;
                ll z = c-b;
                ans = min(ans, x*x+y*y+z*z);
            };
            for (int i = 0; i < 3; ++i) {
                auto&D = (i==0)?R:(i==1?G:B);
                for (int d: D) {
                    for (int j = 0; j < 3; ++j) {
                        if (i != j) {
                            auto &E = (j==0) ? R : (j==1?G:B);
                            auto it = E.lower_bound(d);
                            vector<int> Cat;
                            if (it != E.end()) Cat.push_back(*it);
                            if (it != E.end() && next(it) != E.end()) Cat.push_back(*next(it));
                            if (it != E.begin()) Cat.push_back(*prev(it));
                            for (int e: Cat) {
                                int k = 3-i-j;
                                auto &F = (k==0)?R:(k==1?G:B);
                                int mid = (d+e)/2;
                                auto it = F.lower_bound(mid);
                                if (it != F.end()) test(d, e, *it);
                                if (it != F.end() && next(it) != F.end()) test(d, e, *next(it));
                                if (it != F.begin()) test(d, e, *prev(it));
                            }
                        }
                    }
                }
            }
            cout << ans << '\n';
        }
    }
};
