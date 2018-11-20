#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int A, B, C; cin >> A >> B >> C;
    int X1, Y1, X2, Y2; cin >> X1 >> Y1 >> X2 >> Y2;

    vector<pair<double,double>> D, E;
    if (A != 0) {
        D.push_back({-(Y1 * double(B) + C)/A, Y1});
        E.push_back({-(Y2 * double(B) + C)/A, Y2});
    }
    if (B != 0) {
        D.push_back({X1, -(X1 * double(A) + C)/B});
        E.push_back({X2, -(X2 * double(A) + C)/B});
    }

    double dist = (double)abs(X1-X2) + double(abs(Y1-Y2));
    for (auto d:D) {
        for (auto e:E) {
            dist = min(dist, abs(X1-d.x) + abs(Y1-d.y) + sqrt((d.x-e.x)*(d.x-e.x) + (d.y-e.y)*(d.y-e.y))
                            + abs(X2-e.x) + abs(Y2-e.y));
        }
    }

    cout << fixed << setprecision(10) << dist << endl;

}
};
