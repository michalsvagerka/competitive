#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, T; cin >> N >> T;
    vector2<int> A(N, N, 0);
    for (int i = 0; i < T; ++i) {
        A[0][0] += 1024;
        for (int j = 0; j < N-1; ++j) {
            for (int k = 0; k <= j; ++k) {
                if (A[j][k] >= 1024) {
                    int exc = A[j][k] - 1024;
                    A[j][k] = 1024;
                    A[j+1][k] += exc / 2;
                    A[j+1][k+1] += exc / 2;
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k <= j; ++k) {
            ans += (A[j][k] >= 1024);
        }
    }

    cout << ans << endl;   
}
};
