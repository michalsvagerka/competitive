#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B; cin >> N >> A >> B;
        if (A + B > N + 1 || (ll)A * B < N) {
            cout << "-1\n";
            return;
        }

        vector<int> R(N, 0);
        int g = 0;
        for (int j = 1; j <= A; ++j) {
            int b = min(B, (N-g) - (A-j));
            for (int i = 0; i < b; ++i) {
                R[g+i] = g + b - i;
            }
            g += b;
        }

        cout << R;


    }
};
