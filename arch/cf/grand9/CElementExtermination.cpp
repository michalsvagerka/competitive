#include "../l/lib.h"

class CElementExtermination {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            for (int &a: A) --a;
            vector<int> I(N);
            for (int i = 0; i < N; ++i) {
                I[A[i]] = i;
            }

            int j = A[0];
            int k = 0;
            bool fail = false;
            while (true) {
                while (j < N && I[j] <= k) ++j;
                if (j == N) {
                    fail = true;
                    break;
                } else {
                    k = I[j];
                }

                if (k == N-1) {
                    break;
                }
            }

            cout << (fail?"NO":"YES") << '\n';
        }
    }
};
