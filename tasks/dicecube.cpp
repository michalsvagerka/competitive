#include "../l/lib.h"
// #include "../l/mod.h"

class dicecube {
public:
    void solve(istream& cin, ostream& cout) {
        ll N;
        cin >> N;
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        if (N == 1) {
            cout << a + b + c + d + e + f - max(max(max(a,b),max(c,d)),max(e,f)) << endl;
        } else {
            a = min(a, f);
            b = min(b, e);
            c = min(c, d);
            int side = min(a, min(b, c));
            int edge = a + b + c - max(a, max(b, c));
            int vertex = a + b + c;
            cout << 4 * vertex + (8 * N - 12) * edge + (5 * N - 6) * (N - 2) * side << endl;
        }
    }
};
