#include "../l/lib.h"

class BSeaAndIslands {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        int M = N*N/2 + (N%2);
        if (K > M) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if ((i+j)%2 == 0 && K) {
                        cout << 'L';
                        --K;
                    } else {
                        cout << 'S';
                    }
                }
                cout << '\n';
            }
        }
    }
};
