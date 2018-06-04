#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i] >> B[i];
        }

        if (A == B) {
            cout << 0 << endl;
            return;
        }

        ll ans = 0;
        int mnB = 1000000000;
        for (int i = 0; i < N; ++i) {
            if (A[i] <= B[i]) {
                ans += A[i];
                B[i] -= A[i];
                A[i] = 0;
            } else {
                mnB = min(mnB, B[i]);
                ans += A[i];
            }
        }

        cout << ans - mnB << endl;
    }
};
