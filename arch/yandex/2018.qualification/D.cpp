#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<ll> L(N); cin >> L;
        for (int q = 0; q < Q; ++q) {
            int l, r; cin >> l >> r;
            --l; --r;
            r = min(l+100,r);
            vector<pair<ll,int>> C;
            for (int i = l; i <= r; ++i) {
                C.emplace_back(L[i],i+1);
            }
            sort(C.begin(),C.end());
            bool found = false;
            for (int i = 0; i < (int)C.size()-2; ++i) {
                if (C[i].x + C[i+1].x > C[i+2].x) {
                    cout << C[i].y << ' ' << C[i+1].y << ' ' << C[i+2].y << '\n';
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "-1\n";
            }
        }

    }
};
