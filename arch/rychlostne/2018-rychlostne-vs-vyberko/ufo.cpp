#include "../../../l/lib.h"
#include "../../../l/segtree.h"

struct MinPiiOp { pii operator()(pii a, pii b) const { return (a.x < b.x) ? pii{a.x, std::min(a.y,b.x)} : pii{b.x, std::min(b.y,a.x)}; }};
struct MaxPiiOp { pii operator()(pii a, pii b) const { return (a.x > b.x) ? pii{a.x, std::max(a.y,b.x)} : pii{b.x, std::max(b.y,a.x)}; }};

class ufo {
public:

    map<pii, set<int>> R;
    bool contains(int a, int b, pii q) {
        auto it = R.find(q);
        if (it == R.end()) return false;
        auto it2 = it->y.lower_bound(a);
        auto it3 = it->y.upper_bound(b);
        return it2 != it3;
    }

    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<pii> X(N), Y(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i].x >> Y[i].x;
            X[i].y = Y[i].y = -1e9-7;
            R[{X[i].x, Y[i].x}].insert(i);
        }

        SegTree<pii, MaxPiiOp> MaxX, MaxY;
        MaxX.setup(X); MaxY.setup(Y);

        for (int i = 0; i < N; ++i) {
            X[i].y = Y[i].y = 1e9+7;
        }
        SegTree<pii, MinPiiOp> MinX, MinY;
        MinX.setup(X); MinY.setup(Y);

        for (int q = 0; q < Q; ++q) {
            ui a, b; cin >> a >> b;
            --a; --b;

            pii maxX = MaxX.get(a,b);
            pii maxY = MaxY.get(a,b);
            pii minX = MinX.get(a,b);
            pii minY = MinY.get(a,b);

            int ans = 2e9+7;
            ans = min(ans, max(maxX.x - minX.x, maxY.x - minY.y));
            ans = min(ans, max(maxX.x - minX.x, maxY.y - minY.x));
            ans = min(ans, max(maxX.x - minX.y, maxY.x - minY.x));
            ans = min(ans, max(maxX.y - minX.x, maxY.x - minY.x));
            if (contains(a,b,{minX.x,minY.x})) ans = min(ans, max(maxX.x - minX.y, maxY.x - minY.y));
            if (contains(a,b,{maxX.x,minY.x})) ans = min(ans, max(maxX.y - minX.x, maxY.x - minY.y));
            if (contains(a,b,{minX.x,maxY.x})) ans = min(ans, max(maxX.x - minX.y, maxY.y - minY.x));
            if (contains(a,b,{maxX.x,maxY.x})) ans = min(ans, max(maxX.y - minX.x, maxY.y - minY.x));

            cout << ans << '\n';
        }
    }
};
