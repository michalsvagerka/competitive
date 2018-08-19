#include "../l/lib.h"
// #include "../l/mod.h"

class MaximumWaterfall {
public:

    struct Line {
        pii seg, orig;
        int flow;
    };

void solve(istream& cin, ostream& cout) {
    int N, T; cin >> N >> T;
    vector<pair<int,pii>> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    P.push_back({T,{-1e9,1e9}});
    sort(P.begin(),P.end());

    map<int,Line> D;
    D[-1e9] = {{-1e9,1e9},{-1e9,1e9},int(2e9)};

    auto inter = [](pii &x, pii&s) {
        return max(0, min(x.y,s.y) - max(x.x,s.x));
    };

    for (auto &p : P) {
        pii S = p.y;
        int L = S.x;
        int R = S.y;
        auto it = D.lower_bound(L);
        if (it != D.begin()) {
            --it;
            if (inter(p.y, it->y.seg) == 0) ++it;
        }

        int flow = 0;
        vector<Line> add;

        while (it != D.end() && inter(S, it->y.seg) > 0) {
            it++;
            Line line = prev(it)->y;
            D.erase(prev(it));
            if (inter(line.seg, S) == inter(line.orig, S)) {
                flow = max(flow, min(line.flow, inter(line.seg, S)));
            }

            if (line.seg.x < L) {
                add.push_back({{line.seg.x, L}, line.orig, line.flow});
            }

            if (line.seg.y > R) {
                add.push_back({{R, line.seg.y}, line.orig, line.flow});
            }
        }

        for (Line l : add) D[l.seg.x] = l;
        D[L] = {S, S, flow};

    }

    cout << D.begin()->y.flow << endl;
}
};
