#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int MAX = 500;
constexpr int MAXSQRT = 00;

class chainsaw {
public:

    void solve(istream& cin, ostream& cout) {
        vector2<int> J(MAX+1,MAX+1,-1);
        J[0][0] = 0;
        for (int r = 0; r <= MAXSQRT; ++r) {
            for (int b = 0; b <= MAXSQRT; ++b) {
                if (r == 0 && b == 0) continue;
                for (int ar = MAX-r; ar >= 0; --ar) {
                    for (int ab = MAX-b; ab >= 0; --ab) {
                        if (J[ar][ab]!=-1) {
                            J[ar+r][ab+b] = max(J[ar+r][ab+b], J[ar][ab]+1);
                        }
                    }
                }
            }
        }

        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int R,B;
            cin >> R >> B;
            cout << "Case #" << t << ": " << J[R][B] << '\n';
        }
    }
};
