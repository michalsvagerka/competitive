#include "../l/lib.h"
// #include "../l/mod.h"

class vazenestromy {
public:
    void solve(istream& cin, ostream& cout) {
        int N; ll X; cin >> N >> X;
        vector<ll> S(N, 1);
        for (int i = 1; i < N; ++i) {
            S[i] = S[i-1] * 3;
        }

        for (int i = 0; i < N; ++i) {
            X += S[i];
        }

        vector<int> A,B;
        for (int i = 0; i < N; ++i) {
            int l = X%3;
            if (l == 2) B.push_back(i+1);
            if (l == 0) A.push_back(i+1);
            X /= 3;
        }

        if (X != 0) {
            cout << "-1\n";
            return;
        }

        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        if (A.empty()) cout << endl; else cout << A;
        if (B.empty()) cout << endl; else cout << B;
    }
};
