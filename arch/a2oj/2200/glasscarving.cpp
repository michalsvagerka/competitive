#include "../../../l/lib.h"
// #include "../l/mod.h"

class glasscarving {
public:
    void solve(istream& cin, ostream& cout) {
        int W, H, N; cin >> W >> H >> N;
        vector<map<int,int>> C(2);
        vector<set<pair<int,pii>>> D(2);
        C[0][0] = W;
        D[0].insert({W,{0,W}});
        C[1][0] = H;
        D[1].insert({H,{0,H}});
        for (int i = 0; i < N; ++i) {
            char c; int o;
            cin >> c >> o;
            int j = c == 'H';
            auto it = C[j].lower_bound(o);
            int lo = prev(it)->x;
            int fin = prev(it)->y;
            C[j][o] = fin;
            C[j][lo] = o;
            D[j].insert({fin-o,{o,fin}});
            D[j].insert({o-lo,{lo,o}});

            for (int j = 0; j < 2; ++j) {
                while (C[j][D[j].rbegin()->y.x] != D[j].rbegin()->y.y) D[j].erase(prev(D[j].end()));
            }

            cout << ll(D[0].rbegin()->x) * D[1].rbegin()->x << '\n';
        }
    }
};
