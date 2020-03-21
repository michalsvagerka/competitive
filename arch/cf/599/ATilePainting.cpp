#include "../l/lib.h"

class ATilePainting {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        for (int x = 2; x <= 1000000; ++x) {
            if (N%x == 0) {
                while (N%x == 0) N /= x;
                cout << (N==1?x:1) << endl;
                return;
            }
        }

        cout << N << endl;
    }
};
