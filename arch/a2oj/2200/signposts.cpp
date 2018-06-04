#include "../../../l/lib.h"
#include "../../../l/geo.h"
#include "../../../l/frac.h"
#include "../../../l/matrix.h"

class signposts {
public:

    struct Line {
        int a,b,c;
    };

    int N, K;
    vector<Line> L;
    vector<int> R;
    vector<Point<Fraction>> S;

    bool intersect(const Line&l, const Line&k) {
        return ll(l.a)*k.b != ll(l.b)*k.a;
    }

    Point<Fraction> getIntersection(const Line&l, const Line&k) {
        Matrix<Fraction> W{2,2};
        W[0][0] = l.a; W[0][1] = l.b;
        W[1][0] = k.a; W[1][1] = k.b;
        auto s = W.solveFor({-l.c,-k.c});
        return {s[0],s[1]};
    }

    bool goesThrough(const Line&l, Point<Fraction>&f) {
        return f.x * l.a + f.y * l.b + l.c == 0;
    }

    bool solve(int i) {
        if (i == N) return true;

        bool pnt = false;
        for (auto&s:S) pnt |= goesThrough(L[i], s);
        if (pnt) return solve(i+1);

        bool add = true;
        for (int j = 0; j < K; ++j) {
            if (R[j] == -1 && add) {
                R[j] = i;
                if (solve(i+1)) return true;
                R[j] = -1;
                add = false;
            } else if (R[j] >= 0 && intersect(L[i], L[R[j]])) {
                int o = R[j];
                S.push_back(getIntersection(L[i], L[R[j]]));
                R[j] = -2;
                if (solve(i+1)) return true;
                R[j] = o;
                S.pop_back();
            }
        }

        return false;
    }


    void solve(istream& cin, ostream& cout) {

        cin >> N >> K;
        if (N == 1) {
            cout << "YES\n1\n1 -1\n"; return;
        }
        L.resize(N);
        R = vector<int>(K, -1);
        for (int i = 0; i < N; ++i) {
            cin >> L[i].a >> L[i].b >> L[i].c;
        }

        if (solve(0)) {
            cout << "YES\n";
            cout << K << "\n";
            for (auto&s:S) {
                vector<int> Z;
                for (int i = 0; i < N; ++i) {
                    if (goesThrough(L[i],s)) Z.push_back(i);
                }
                cout << Z[0]+1 << ' ' << Z[1]+1 << '\n';
            }
            for (int j = 0; j < K; ++j) {
                if (R[j] == -1) {
                    cout << "1 -1\n";
                } else if (R[j] >= 0) {
                    cout << R[j]+1 << ' ' << -1 << '\n';
                }
            }
        } else {
            cout << "NO\n";
        }

    }
};
