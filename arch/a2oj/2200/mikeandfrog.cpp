#include "../../../l/lib.h"
// #include "../l/mod.h"

class mikeandfrog {
public:
    struct Result {
        int before;
        int period;
        int first;
    };


    Result check(ll h, int a, int x, int y, int M) {
        Result R{-1,-1,-1};
        vector<int> T(M, -1);
        int t;
        for (t = 0; T[h] == -1; ++t) {
            if (a == h && R.first == -1) {
                R.first = t;
            }

            T[h] = t;
            h = (h*x + y)%M;
        }
        R.before = T[h];
        R.period = t-T[h];
        return R;
    }

    void solve(istream& cin, ostream& cout) {
        int M; cin >> M;
        int H1, A1, X1, Y1; cin >> H1 >> A1 >> X1 >> Y1;
        int H2, A2, X2, Y2; cin >> H2 >> A2 >> X2 >> Y2;

        Result R1 = check(H1, A1, X1, Y1, M);
        Result R2 = check(H2, A2, X2, Y2, M);
        if (R1.first == -1 || R2.first == -1) {
            cout << "-1\n";
        } else if (R1.first < R1.before) {
            if (R2.first == R1.first) {
                cout << R1.first << '\n';
            } else if (R2.first < R2.before) {
                cout << "-1\n";
            } else if (R2.first < R1.first && (R1.first - R2.first)%R2.period == 0) {
                cout << R1.first << '\n';
            } else {
                cout << "-1\n";
            }
        } else if (R2.first < R2.before) {
            if (R1.first == R2.first) {
                cout << R2.first << '\n';
            } else if (R1.first < R1.before) {
                cout << "-1\n";
            } else if (R1.first < R2.first && (R2.first - R1.first)%R1.period == 0) {
                cout << R2.first << '\n';
            } else {
                cout << "-1\n";
            }
        } else {
            ll p1 = R1.first;
            ll p2 = R2.first;
            while (p1 != p2 && p1 < R1.first + R2.first + ll(R1.period) * R2.period) {
                if (p1 < p2) p1 += R1.period;
                if (p2 < p1) p2 += R2.period;
            }
            if (p1 == p2) {
                cout << p1 << endl;
            } else {
                cout << "-1\n";
            }
        }


    }
};
