#include "../l/lib.h"
#include "../l/segtree.h"
#include <numeric>

class DZYLovesColors {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    AddSumTree<ll> T;
    T.setup(N, 0);
    set<pair<pii,int>> E;
    for (int i = 0; i < N; ++i) E.insert({{i,i},i+1});
    
    for (int i = 0; i < M; ++i) {
        int t, l, r; cin >> t >> l >> r;
        --l; --r;
        if (t == 1) {
            int x; cin >> x;
            vector<pair<pii,int>> A;
            auto it = E.lower_bound({{l,-1},0});
            if (it == E.end() || it->x.x > l) --it;

            A.push_back({{l,r},x});
            if (it->x.x < l) A.push_back({{it->x.x, l-1}, it->y});

            while (it != E.end() && it->x.x <= r) {
                T.put(max(l, it->x.x), min(r, it->x.y), abs(it->y-x));
                if (it->x.y > r) A.push_back({{r+1, it->x.y}, it->y});
                it++;
                E.erase(prev(it));
            }

            for (auto&a:A) E.insert(a);
        } else {
            cout << T.get(l, r) << '\n';
        }
    }
}
};
