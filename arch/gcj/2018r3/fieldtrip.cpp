#include "../l/lib.h"
// #include "../l/mod.h"

class fieldtrip {
public:
struct Calc {

    int N, ans;
    vector<pii> P;

    void calc() {
        int lox = P[0].x, hix = P[0].x, loy = P[0].y, hiy = P[0].y;
        for (pii&p:P) {
            lox = min(lox, p.x);
            hix = max(hix, p.x);
            loy = min(loy, p.y);
            hiy = max(hiy, p.y);
        }

        ans = max((hiy - loy + 1)/2, (hix - lox + 1)/2);
    }

    void read(istream& cin) {
        cin >> N;
        P.resize(N);
        cin >> P;
    }

    void write(ostream &cout) {
        cout << ans;
        cout << '\n';
    }
};


void solve(istream& cin, ostream& cout) {
    ui T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        Calc c;
        c.read(cin);
        c.calc();
        cout << "Case #" << t << ": ";
        c.write(cout);
    }
}
};
