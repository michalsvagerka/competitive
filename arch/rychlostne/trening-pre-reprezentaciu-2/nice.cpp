#include "../l/lib.h"
#include "../l/matrix.h"
#include "../l/runtimemod.h"


class nice {
public:
    void solve(istream& cin, ostream& cout) {
        ull N;
        ui M, P; cin >> N >> M >> P;
        if (P == 1) {
            cout << "0\n";
            return;
        }

        if (N == 1) {
            cout << (1<<M)%P << '\n';
            return;
        }

        Matrix<RField> A(1<<M,1<<M,RField{0,P});
        for (int j = 0; j < (1<<M); ++j) {
            for (int k = 0; k < (1<<M); ++k) {
                bool ok = true;
                for (int l = 0; l < M-1; ++l) {
                    int m = (j>>l)&3, n = (k>>l)&3;
                    ok &= ((m+n)%6 != 0);
                }
                if (ok) A[j][k] = RField{1,P};
            }
        }

        auto B = A.power(N-1);


        RField ans = 0;
        for (int i = 0; i < (1<<M); ++i) {
            for (int j = 0; j < (1<<M); ++j) {
                ans += B[i][j];
            }
        }
        cout << ans << endl;
    }
};
