#include "../l/lib.h"
#include <numeric>
// #include "../l/mod.h"

class Stars {
public:
void solve(istream& cin, ostream& cout) {
    long double PI = acos(-1.0);
    long double side = 10;
    long double sqrlen = 261.8033988749894;
    long double xt = side/2;
    long double yt = sqrt(sqrlen - xt*xt);
    long double xl = (sqrt(sqrlen) - side)/2;
    long double yl = sqrt(side*side - xl*xl);

    int N; cin >> N;
    vector<pair<long double,long double>> W;
    W.emplace_back(0,0);
    for (int i = 0; i < N; ++i) {
        W.emplace_back(i*side/2 + side, i*yt);
        W.emplace_back(i*side/2 - xl, i*yt + yl);
        W.emplace_back(i*side/2 + side + xl, i*yt + yl);
        W.emplace_back(i*side/2 + xt, i*yt + yt);
    }



    vector<int> Rep;
    for (int i = 0; i <= N; ++i) Rep.push_back(4*i+1);
    for (int i = N-1; i >= 0; --i) {
        Rep.push_back(4*i+2);
        Rep.push_back(4*i+3);
        Rep.push_back(4*i+4);
        Rep.push_back(4*i+1);
    }
//
//    for (int i = 0; i < Rep.size()-1; ++i) {
//        long double dx = (W[Rep[i]-1].x - W[Rep[i+1]-1].x);
//        long double dy = W[Rep[i]-1].y - W[Rep[i+1]-1].y;
//        cout << dx*dx+dy*dy << ' ';
//    }
//    cout << endl;
//

    cout << 4*N + 1 << '\n';
    cout << fixed << setprecision(12);
    for (auto&w:W) cout << w << '\n';

    vector<int> Z(5);
    for (int i = 0; i < N; ++i) {
        cout << 4*i+1 << ' ' << 4*i+2 << ' ' << 4*i+4 << ' ' << 4*i+5 << ' ' << 4*i+3 << '\n';
    }
    cout << Rep;
}
};
