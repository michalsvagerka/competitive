#include "../../../l/lib.h"
#include "../../../l/geo.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<Point<ll>> A(N); cin >> A;
        cout << fixed << setprecision(20);

        vector<Point<ll>> H;
        for (int i = 0; i < N; ++i) {
            bool fail = false;
            for (int j = 0; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    if (i==j || i==k) continue;
                    if (Segment<ll>{A[j],A[k]}.contains(A[i])) {
//                        cout << A[i] << " lies on " << A[j] << ' ' << A[k] << endl;
                        fail = true;
                    };
                }
            }
            if (!fail) H.push_back(A[i]);
        }

//        cerr << N << ' ' << H.size() << endl;

        if (N == 2) {
            cout << "0.5\n0.5\n";
        } else {
            map<Point<ll>,double> Q;
            double sum = 0;

            ll lx = A[0].x, ly = A[0].y, hx = A[0].x, hy = A[0].y;
            for (int i = 0; i < N; ++i) {
                lx = min(lx, A[i].x);
                hx = max(hx, A[i].x);
                ly = min(ly, A[i].y);
                hy = max(hy, A[i].y);
            }
            if (lx == hx) {
                Q[{lx,ly}] = Q[{lx,hy}] = 1;
                sum = 2;
            } else if (ly == hy) {
                Q[{lx,ly}] = Q[{hx,ly}] = 1;
                sum = 2;
            } else {
                auto B = convexhull(H);
                if (B.size() == 2) {
                    sum = 2;
                    Q[{lx,ly}] = Q[{hx,ly}] = Q[{hx,hy}] = Q[{lx,hy}] = 1;
                } else {

                    for (int i = 0; i < B.size(); ++i) {
                        auto a = B[i], b = B[(i + 1) % B.size()], c = B[(i + 2) % B.size()];
                        double arccos = ((b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y));
                        arccos /= sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
                        arccos /= sqrt((b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y));
                        double angle = acos(arccos);
                        Q[b] = PI - angle;
                        sum += Q[b];
                    }
                }

//                cout << B.size() << endl;
            }

            for (int i = 0; i < N; ++i) {
                cout << Q[A[i]]/sum << '\n';
            }
        }
    }
};
