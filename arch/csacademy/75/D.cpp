#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> C(N), T(N);
        set<pii> W;
        for (int i = 0; i < N; ++i) {
            cin >> C[i] >> T[i];
            W.insert({T[i],i});
        }

        vector<ll> Ans(N, -1);
        map<int,int> L;
        ll t = 0;
        for (pii w:W) {
            while (!L.empty() && t < w.x) {
                if (t + L.begin()->y <= w.x) {
                    t += L.begin()->y;
                    Ans[L.begin()->x] = t;
                    L.erase(L.begin());
                } else {
                    L.begin()->y -= (w.x - t);
                    t = w.x;
                }
            }

            t = w.x;
            L[w.y] = C[w.y];
        }

        while (!L.empty()) {
            t += L.begin()->y;
            Ans[L.begin()->x] = t;
            L.erase(L.begin());
        }


        for (int i = 0; i < N; ++i) {
            cout << Ans[i] << '\n';
        }
    }
};
