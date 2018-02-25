#include <numeric>
#include "../../../l/lib.h"
#include "../../../l/suffixarray.h"

class guesssub {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();

        S += '$';
        SuffixArray<int, true> T(S);
        vector<int> L(N, 0);
        int Z = (N+1)*N/2;
        map<int, int> Q;
        for (int i = 1; i < N+1; ++i) {
            for (int j = 0; j < N-T.S[i]; ++j) ++L[j];
            for (int j = T.lcp(T.S[i]); j < N-T.S[i]; ++j) Q[L[j]]++, L[j] = 0;
        }
        ll ans = 0;
        while (Q.begin()->x != Z) {
            int v = Q.begin()->x;
            int w = Q.begin()->y;
            ans += v * w;
            if (w >= 2) Q[2 * v] += w / 2;
            Q.erase(Q.begin());
            if (w % 2) {
                int u = Q.begin()->x;
                int z = Q.begin()->y;
                Q[v + u]++;
                ans += u;
                if (z == 1) {
                    Q.erase(Q.begin());
                } else {
                    Q.begin()->y--;
                }
            }
        }

        cout << fixed << setprecision(16) << ans/((N+1)*N/2.0) << endl;
    }
};
