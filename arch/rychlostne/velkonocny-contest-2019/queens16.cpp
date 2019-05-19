#include "../l/lib.h"

class queens16 {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<bool> R(50, false), C(50, false), P(100,false), M(100,false);
        for (int i = 0; i < N; ++i) {
            int r, c; cin >> r >> c;
            R[r] = true;
            C[c] = true;
            P[r+c] = true;
            M[r-c+50] = true;
        }

        int Q; cin >> Q;
        for (int r = 0; r < 50; ++r) {
            for (int c = 0; c < 50; ++c) {
                if (Q && !R[r] && !C[c] && !P[r+c] && !M[r-c+50]) {
                    Q--;
                    R[r] = true;
                    C[c] = true;
                    P[r+c] = true;
                    M[r-c+50] = true;
                    cout << r << ' ' << c << endl;
                }
            }
        }
    }
};
