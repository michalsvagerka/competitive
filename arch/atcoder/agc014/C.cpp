#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int H,W,K; cin >> H >> W >> K;
        vector<string> A(H); cin >> A;
        minheap<pair<pii,pii>> Q;
        vector2<pii> D(H,W,{1e9,1e9});
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                if (A[h][w] == 'S') {
                    D[h][w] = {0,0};
                    Q.push({{0,0},{h,w}});
                }
            }
        }

        auto cel = [=](int r) { return (r+K-1)/K; };
        auto up = [=](int r) { return K*cel(r); };

        while (!Q.empty()) {
            auto q = Q.top(); Q.pop();
            if (D[q.y.x][q.y.y] != q.x) continue;
            if (q.y.x == 0 || q.y.x == H-1 || q.y.y == 0 || q.y.y == W-1) {
                cout << cel(q.x.x) << endl;
                return;
            }
            for (int dh : {-1,0,1}) {
                for (int dw : {-1,0,1}) {
                    if (abs(dh+dw) == 1) {
                        int h = q.y.x + dh;
                        int w = q.y.y + dw;
                        int m = q.x.x + 1;
                        int l = q.x.y;
                        if (A[h][w] == '#') {
                            ++l;
                            if (cel(m) == cel(l)) m = up(m) + 1;
                        }
                        if (pii{m,l} < D[h][w]) {
                            D[h][w] = {m,l};
                            Q.push({{m,l},{h,w}});
                        }
                    }
                }
            }
        }
    }
};
