#include "../l/lib.h"
 #include "../l/mod.h"

class EBBQHard {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    auto F = FieldMod::fact(8001);
    auto I = FieldMod::invfact(8001);

    vector2<FieldMod> D(4001,4001,0);
    for (int i = 0; i < N; ++i) {
        D[2000-A[i]][2000-B[i]]++;
    }

    for (int i = 0; i <= 4000; ++i) {
        for (int j = 0; j <= 4000; ++j) {
            if (i != 0) D[i][j] += D[i-1][j];
            if (j != 0) D[i][j] += D[i][j-1];
        }
    }

    FieldMod ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += D[2000+A[i]][2000+B[i]];
        ans -= F[2*A[i]+2*B[i]] * I[2*A[i]] * I[2*B[i]];
    }
    cout << ans/2 << '\n';
}
};
