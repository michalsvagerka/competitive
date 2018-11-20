#include "../l/lib.h"
#include "../l/geo.h"

typedef pair<double,double> pdd;

class sviecky {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, R; cin >> N >> M >> R;
    vector<double> X(N), Y(N);
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    vector<Point<double>> P;
    vector<Line<double>> L;
    for (int j = 0; j < M; ++j) {
        int a, b, c;
        cin >> a >> b >> c;
        A[j] = a;
        B[j] = b;
        C[j] = c;

        if (a == 0) {
            L.push_back({{0, -double(c)/b}, {1, -double(c)/b}});
        } else if (b == 0) {
            L.push_back({{-double(c)/a, 0}, {-double(c)/a, 1}});
        } else if (c == 0) {
            L.push_back({{1, -double(b)/a}, {2, -2*double(b)/a}});
        } else {
            L.push_back({{0, -double(c)/b}, {-double(c)/a, 0}});
        }
    }

    for (int i = 0; i < M; ++i) {
        P.push_back(L[i].project({0,0}));
        for (int j = i+1; j < M; ++j) {
            if (A[i]*B[j] == A[j]*B[i]) continue;
            auto inter = L[i].intersection(L[j]);
            P.push_back(inter);
        }
    }

    map<int,int> Or;
    for (auto p: P) {
        if (p.distance(Point<double>{0,0}) > R) continue;
        Point<double> G = {p.x, p.y};

        int m = 0, l = 0;
        for (int i = 0; i < M; ++i) {
            int o = orientation(L[i].x, L[i].y, G);
            if (o == 0) l |= 1<<i;
            if (o == 1) m |= 1<<i;
        }
        vector<int> Z{m};
        for (int j = 0; j < M; ++j) {
            if (l&(1<<j)) {
                int k = Z.size();
                for (int t = 0; t < k; ++t) Z.push_back(Z[t] | (1<<j));
            }
        }

        for (int s: Z) Or[s] = 0;
    }

    for (int j = 0; j < N; ++j) {
        int m = 0;
        for (int i = 0; i < M; ++i) {
            int o = orientation(L[i].x, L[i].y, Point<double>{X[j],Y[j]});
            if (o == 0) { m = -1; break; };
            if (o == 1) m |= 1<<i;
        }
        if (m != -1) Or[m]++;
    }


    bool ok = true;
    for (auto o: Or) {
        if (o.y != 1) ok = false;
    }

    cout << (ok ? "yes" : "no") << endl;
}
};
