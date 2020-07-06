#include "../l/lib.h"
#include "../l/mod.h"

class CRangeSet {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int A, B; cin >> A >> B;
        if (A > B) swap(A, B);

        vector<FieldMod> BVal(B+2, 0);
        BVal[0] = 1;
        for (int i = 1; i < B+2; ++i) {
            BVal[i] += BVal[i-1];
            for (int j = A; j + i + 1 < B+2; ++j) BVal[i+j+1] += BVal[i];
        }

        vector2<FieldMod> D(N+2, 2, 0);
        D[0][0] = D[0][1] = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j < A && i + j <= N; ++j) D[i+j][0] += D[i][1];
            for (int j = 1; j < B && i + j <= N; ++j) D[i+j][1] += D[i][0] * BVal[j + (i == 0) + (i+j==N)];
        }

        FieldMod ans = FieldMod{2}.pow(N) - (D[N][0] + D[N][1]);
        cout << ans << '\n';
    }
};
