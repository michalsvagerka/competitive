#include "../l/lib.h"

class DCoffeeVarietiesHardVersion {
public:
    void solve(istream& cin, ostream& cout) {
//        for (int n = 0; n <= 10; ++n) {
//            for (int k = 1; k <= n; ++k) {
//                int N = 1<<n; int K = 1<<k;
//                int ans = K;
//                for (int j = K; j < N; j += K/2) {
//                    int batches = j/K;
//                    int over = j%K;
//                    ans += batches * (3*K/2);
//                    if (over) ans += K;
//                }
//                cout << (3*N*N/(2*K) >= ans) << endl;
//            }
//        }



        int N, K; cin >> N >> K;

        // TODO: K == 1!!!
        vector<bool> Distinct(N, true);

        auto check = [&](int i) {
            cout << "? " << i+1 << endl;
            char c; cin >> c;
            if (c == 'Y') Distinct[i] = false;
        };
        for (int i = 0; i < K; ++i) check(i);

        int S = K/2;
        if (S == 0) S = 1;
        for (int j = K; j < N; j += S) {
            cout << "R" << endl;

            int cur = 0;
            for (int i = 0; i < j; ++i) {
                if (Distinct[i]) {
                    check(i);
                    cur++;
                    if (cur == S) {
                        for (int l = 0; l < S; ++l) check(j+l);
                        cur -= 2*S;
                    }
                    if (cur == 0) {
                        cout << "R" << endl;
                    }
                }
            }
            if (cur > 0) for (int l = 0; l < S; ++l) check(j+l);
        }

        cout << "! " << count(Distinct.begin(),Distinct.end(),true) << '\n';
    }
};
