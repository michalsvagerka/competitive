#include "../l/lib.h"
// #include "../l/mod.h"

class zvyskostroj {
public:
    void solve(istream& cin, ostream& cout) {
        vector3<vector<int>> V(10, 10, 10);
        vector3<int> PP(10, 10, 10), P(10, 10, 10);
        for (int q = 2; q < 10; ++q) {
            for (int p0 = 1; p0 < 10; ++p0) {
                for (int p1 = 0; p1 < 10; ++p1) {
                    int a = p0, b = p1;
                    int r = (10*a+b)%q;
                    map<pair<pii,int>,int> Z;
                    Z[{{p0,p1},r}] = 0;
                    V[q][p0][p1].push_back(r);
                    for (int l = 1; ; ++l) {
                        a = (4*b + a)%q;
                        swap(a,b);
                        r = (10*r+b)%q;
                        auto it = Z.find({{a,b},r});
                        if (it != Z.end()) {
                            PP[q][p0][p1] = it->y;
                            P[q][p0][p1] = l - it->y;
                            break;
                        } else {
                            V[q][p0][p1].push_back(r);
                            Z[{{a,b},r}] = l;
                        }
                    }
                }
            }
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int p0, p1, q; ll n; cin >> p0 >> p1 >> q >> n;
            if (q == 1) {
                cout << "0\n";
            } else {
                n -= 2;
                int pp = PP[q][p0][p1];
                int p = P[q][p0][p1];
                if (n >= pp) {
                    n -= pp;
                    n %= p;
                    n += pp;
                }
                cout << V[q][p0][p1][n] << '\n';
            }
        }
    }
};
