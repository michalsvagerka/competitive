#include <numeric>
#include "../../../l/lib.h"
#include "../../../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        auto F = FieldMod::fact(N);
        auto I = FieldMod::invfact(N);

        FieldMod ans = F[N-1] * (N-1);

        FieldMod tot = 0;
        for (int i = 1; ; ++i) {
            if (N-2-i < i) break;

            ans -= F[N-2-i] * I[N-2-i-i] * F[N-1-i];
        }


        cout << ans << endl;

//        int ans = 0;
//        vector<int> P(N-1);
//        iota(P.begin(),P.end(),0);
//        do {
//            vector<bool> S(N, true);
//            int c = N;
//            for (int i = 0; i < N-1; ++i) {
//                c -= S[P[i]];
//                c -= S[P[i]+1];
//                S[P[i]] = false;
//                S[P[i]+1] = false;
//                if (c == 0) { ans += i+1; break; }
//            }
//        } while (next_permutation(P.begin(),P.end()));
//        cout << ans << '\n';
    }
};
