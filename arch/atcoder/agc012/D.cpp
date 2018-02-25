#include "../../../l/lib.h"
#include "../../../l/util.h"
#include "../../../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N,X,Y; cin >> N >> X >> Y;
        pii lo{1e9+7, 1e9+7};
        vector<pii> L(N);
        for (int i = 0; i < N; ++i) {
            int c,w; cin >> c >> w;
            --c;
            L[i] = {w,c};
        }
        sort(L.begin(),L.end());
        vector<int> P(N, -1);
        for (int i = N-1; i >= 0; --i) P[L[i].y] = i;

        int l = 0;
        while (l < N && L[0].y == L[l].y) ++l;

        UnionFind U(N);
        for (int i = 1; i < N; ++i) {
            if (L[P[L[i].y]].x + L[i].x <= X) U.unite(P[L[i].y], i);
            if (L[0].y != L[i].y && L[0].x + L[i].x <= Y) U.unite(0, i);
            if (l != N && L[l].y != L[i].y && L[l].x + L[i].x <= Y) U.unite(l, i);
        }
        map<int,map<int,int>> C;
        for (int i = 0; i < N; ++i) {
            C[U.find(i)][L[i].y]++;
        }

        auto F = FieldMod::fact(N);
        auto I = FieldMod::invfact(N);

        FieldMod ans = 1;
        for (auto &c:C) {
            int tot = 0;
            for (auto &cc: c.y) {
                ans *= I[cc.y];
                tot += cc.y;
            }
            ans *= F[tot];
        }
        cout << ans << endl;

    }
};
