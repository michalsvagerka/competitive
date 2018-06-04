#include "../../../l/lib.h"
#include "../../../l/geo.h"
#include "../../../l/frac.h"

class runningsheep {
public:
    void solve(istream& cin, ostream& cout) {
        int A; cin >> A;
        vector<Point<ll>> P(A); cin >> P;
        P.push_back(P[0]);
        P.push_back(P[1]);

        int B; cin >> B;
        vector<Point<ll>> Q(B); cin >> Q;
        Q.push_back(Q[0]);
        Q.push_back(Q[1]);

        map<Fraction, int> T;
        int posX = -1;
        int negX = -1;
        for (int i = 0; i < A; ++i) {
            Segment<ll> S{P[i], P[i+1]};
            ll x = S.dx(), y = S.dy();
            if (y == 0) {
                if (x < 0) negX = i; else posX = i;
            } else {
                T[Fraction{x,y}] = i;
            }
        }

        for (int i = 0; i < B; ++i) {
            Segment<ll> S{Q[i+1], Q[i]};
            ll x = S.dx(), y = S.dy();
//            cerr << Fraction{x,y} << endl;
            int l = -1;
            if (y == 0) l = x < 0 ? negX : posX;
            else {
                auto it = T.find(Fraction{x,y});
                if (it != T.end()) l = it->y;
            }

            if (l != -1) {
//                cerr << P[l] << ' ' << P[l+1] << ' ' << Q[i] << ' ' << Q[i+1] << endl;
                if (orientation(P[l], P[l+1], Q[i]) == -1
                    && orientation(Q[i], Q[i+1], P[l]) == -1) {
//                    cerr << P[l] << ' ' << P[l+1] << ' ' << Q[i] << ' ' << Q[i+1] << endl;
                    if (acuteAngle(P[l], P[l+1], Q[i]) && acuteAngle(Q[i+1], Q[i], P[l+1])) {
                        cout << "YES\n";
                        return;
                    }
                }
            }
        }
        cout << "NO\n";
    }
};
