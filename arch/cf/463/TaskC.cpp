#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B; cin >> N >> A >> B;
        for (int i = 0; i*A <= N; ++i) {
            if ((N-i*A)%B == 0) {
                int j = (N-i*A)/B;
                vector<int> P(N);
                int t = 0;
                for (int k = 0; k < i; ++k) {
                    for (int z = 0; z < A-1; ++z) {
                        P[t+z] = t+z+2;
                    }
                    P[t+A-1] = t+1;
                    t+=A;
                }

                for (int k = 0; k < j; ++k) {
                    for (int z = 0; z < B-1; ++z) {
                        P[t+z] = t+z+2;
                    }
                    P[t+B-1] = t+1;
                    t += B;
                }

                cout << P;
                return;
            }
        }


        cout << "-1\n";
    }
};
