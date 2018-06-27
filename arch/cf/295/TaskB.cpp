#include "../../../l/lib.h"
 #include "../../../l/mod.h"

typedef Field<1000000009> F;

class TaskB {
public:
    unordered_map<pii, int> Y;
    map<int, pii> C;

    bool contains(pii v) const { return Y.find(v) != Y.end(); }
    int supportCount(pii v) const { return contains({v.x-1,v.y-1}) + contains({v.x,v.y-1}) + contains({v.x+1,v.y-1}); }

    bool canRemove(pii v) const {
        for (int dx = -1; dx <= 1; ++dx) {
            if (contains({v.x+dx, v.y+1}) && supportCount({v.x+dx, v.y+1}) == 1) {
                return false;
            }
        }
        return true;
    }

    void remove(int r, pii v) {
        C.erase(r);
        Y.erase(v);
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -1; dy <= 0; ++dy) {
                auto it = Y.find({v.x + dx, v.y + dy});
                if (it != Y.end()) {
                    C.erase(it->y);
                    if (canRemove(it->x)) {
                        C[it->y] = it->x;
                    }
                }
            }
        }
    }

void solve(istream& cin, ostream& cout) {
    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        pii x; cin >> x;
        Y.insert({x, i});
    }

    for (auto y:Y) {
        if (canRemove(y.x)) {
            C[y.y] = y.x;
        }
    }

    F ans = 0;
    bool turn = false;
    for (int i = 0; i < M; ++i) {
        auto it = turn ? C.begin() : prev(C.end());
        ans *= M;
        ans += it->x;
        remove(it->x, it->y);
        turn = !turn;
    }
    cout << ans << endl;
}
};
