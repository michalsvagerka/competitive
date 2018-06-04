#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
//
//
//    ll solve(int a, int b) {
//        if (a == b) return 0;
//        if (a < b) return -1;
//        auto it = X.find({a,b});
//        if (it != X.end()) return it->y;
//
//        for (int i = b+1; i < a; ++i) {
//            ll r = solve(a%i, b);
//            if (r != -1) {
//                return X[{a,b}] = (1LL<<i)|r;
//            }
//        }
//
//        return -1;
//    }
//

    void solve(istream& cin, ostream& cout) {
        int N;cin >> N;
        vector<int> A(N), B(N); cin >> A >> B;

        vector3<bool> D(51,51,51,false);
        for (int i = 0; i <= 50; ++i) {
            for (int j = 0; j <= 50; ++j) D[i][i][j] = true;
            for (int j = 1; j <= 50; ++j) {
                for (int k = i+1; k <= 50; ++k) {
                    if (D[k][i][j-1]) {
                        D[k][i][j] = true;
                    } else {
                        D[k][i][j] = D[k][i][j] || D[k%j][i][j];
                    }
                }
            }
        }

        vector2<bool> I(N,51,false);
        for (int i = 0; i < N; ++i) {
            if (!D[A[i]][B[i]][50]) {
                cout << "-1\n";
                return;
            }
            I[i][A[i]] = true;
        }

        ll ans = 0;
        for (int i = 50; i >= 1; --i) {
            bool allOk = true;
            for (int j = 0; j < N; ++j) {
                bool ok = false;
                for (int k = 0; k <= 50; ++k) {
                    ok |= I[j][k] && D[k][B[j]][i-1];
                }
                allOk &= ok;
            }
            if (!allOk) {
                ans |= 1LL<<i;
                for (int j = 0; j < N; ++j) {
                    for (int k = 0; k <= 50; ++k) {
                        if (I[j][k]) {
                            I[j][k%i] = true;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
};
