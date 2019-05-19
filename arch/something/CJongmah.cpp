#include "../l/lib.h"
// #include "../l/mod.h"

class CJongmah {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector3<ll> D(N+1, 3, 3, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    if (j+k+l <= A[i]) {
                        D[i+1][k][l] = max(D[i+1][k][l], D[i][j][k] + l + (A[i]-j-k-l)/3);
                    }
                }
            }
        }
    }
    
    cout << D[N][0][0] << '\n';
}
};
