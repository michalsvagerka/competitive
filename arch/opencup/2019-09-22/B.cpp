#include "../l/lib.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        bool mia = S == "Mia";
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            vector<int> A(64); cin >> A;
            if (mia) {
                int x; cin >> x; --x;
                for (int i = 0; i < 64; ++i) {
                    if (A[i]) x ^= i;
                }
                A[x] ^= 1;
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 8; ++j) {
                        cout << A[i*8+j] << " \n"[j==7];
                    }
                }
                cout << "---\n";
            } else {
                string Minus; cin >> Minus;
                int x = 0;
                for (int i = 0; i < 64; ++i) {
                    if (A[i]) x ^= i;
                }
                cout << x+1 << '\n';
            }
        }
    }
};
