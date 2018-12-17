#include "../l/lib.h"
// #include "../l/mod.h"

class DGridGame {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W, N; cin >> H >> W >> N;
        vector<pii> A(N); cin >> A;
        set<pii> S;
        for (pii&a:A) { --a.x; --a.y; S.insert(a); }
        vector<int> LOY(H, 1e9);
        for (pii a:A) {
            LOY[a.x] = min(LOY[a.x], a.y);
        }

        int z = 0;
        for (int i = 1; i < H; ++i) {
            if (LOY[i] <= z) {
                cout << i << endl;
                return;
            }

            if (S.find({i, z+1}) == S.end()) ++z;
        }

        cout << H << '\n';
    }
};
