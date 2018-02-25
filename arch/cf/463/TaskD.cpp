#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
        int Q, t, last = 0;
        ll p,q;
        cin >> Q;
        vector<vector<pair<int,ll>>> E{{}};
        vector<int> W{0};
        while (Q--) {
            cin >> t >> p >> q;
            p ^= last;
            q ^= last;
            p--;
            if (t == 1) {
                W.push_back(int(q));
                for (int z = 20; z >= 0; --z) {
                    if (z < E[p].size() && W[E[p][z].x] < q) {
                        p = E[p][z].x;
                    }
                }

                if (W[p] < q && !E[p].empty()) {
                    p = E[p][0].x;
                }

                E.emplace_back();
                if (W[p] >= q) {
                    E.back().emplace_back(p,q);
                    ll r = q;
                    for (int i = 0; i < E[p].size() ;++i) {
                        E.back().emplace_back(E[p][i].x, r + E[p][i].y);
                        r += E[p][i].y;
                        p = E[p][i].x;
                    }
                }
            } else if (t == 2) {
                last = 0;
                for (int z = 20; z >= 0; --z) {
                    if (z < E[p].size() && E[p][z].y <= q) {
                        q -= E[p][z].y;
                        p = E[p][z].x;
                        last += 1<<z;
                    }
                }

                if (W[p] <= q) {
                    q -= W[p];
                    last++;
                }

                cout << last << "\n";
            }

        }
    }
};
