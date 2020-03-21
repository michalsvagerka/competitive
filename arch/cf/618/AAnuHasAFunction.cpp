#include "../l/lib.h"

class AAnuHasAFunction {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> C(30, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 30; ++j) {
                if (A[i]&1<<j) C[j]++;
            }
        }

        pii best = {-1, -1};
        for (int i = 0; i < N; ++i) {
            int k = 0;
            for (int j = 0; j < 30; ++j) {
                if (C[j] == 1 && (A[i]&1<<j)) k |= 1<<j;
            }
            best = max(best, {k, i});
        }

        cout << A[best.y];
        for (int i = 0; i < N; ++i) {
            if (i != best.y) cout << ' ' << A[i];
        }
        cout << endl;
    }
};
