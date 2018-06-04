#include "../../../l/lib.h"
#include "../../../l/avl.h"
#include "../../../l/frac.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N, X, Y; cin >> N >> X >> Y;
        vector<pii> C(N); cin >> C;

        avl<pair<Fraction,int>, int> Normal, Slowed;
        for (int i = 0; i < N; ++i) {
            Normal.insert({Fraction{C[i].x,C[i].y}, i}, i);
            Slowed.insert({Fraction{C[i].x,C[i].y-Y}, i}, i);
        }

        for (int i = 0; i < N; ++i) {
            cout << 1 + min(Normal.smaller({Fraction{C[i].x,C[i].y+X}, i}), Slowed.smaller({Fraction{C[i].x,C[i].y}, i})) << '\n';
        }

    }
};
