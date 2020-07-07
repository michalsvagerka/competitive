#include "../../../l/lib.h"
#include "../../../l/geo.h"

class CTwoSquares {
public:
    void solve(istream& cin, ostream& cout) {
        vector<Point<ll>> A(4), B(4); cin >> A >> B;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (Segment(A[i],A[(i+1)%4]).intersect(Segment(B[j],B[(j+1)%4]))) {
                    cout << "YES\n";
                    return;
                }
            }
        }

        for (int t = 0; t < 2; ++t) {
            for (int j = 0; j < 4; ++j) {
                bool ok = true;
                for (int i = 0; i < 3; ++i) {
                    ok &= orientation(A[i],A[i+1],B[j]) == orientation(A[3],A[0],B[j]);
                }
                if (ok) {
                    cout << "YES\n";
                    return;
                }
            }

            swap(A,B);
        }


        cout << "NO\n";
    }
};
