#include "../l/lib.h"
#include "../l/util.h"


// 15 min
class DUniquePath {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<pii> A, B;
        for (int i = 0; i < Q; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            (c?B:A).emplace_back(a,b);
        }

        if (M == N-1 && !B.empty()) {
            cout << "No\n";
            return;
        }

        UnionFind UF(N);
        for (pii a: A) UF.unite(a.x, a.y);
        for (pii b: B) if (UF.united(b.x, b.y)) {
            cout << "No\n";
            return;
        }

        if (M > N - UF.comp + ll(UF.comp) * ll(UF.comp - 1) / 2) {
            cout << "No\n";
            return;
        }

        cout << "Yes\n";
    }
};
