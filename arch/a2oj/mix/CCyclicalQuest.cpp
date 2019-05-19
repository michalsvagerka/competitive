#include "../l/lib.h"
#include "../l/suffixarray.h"
#include "../l/fenwick.h"
#include "../l/random.h"

constexpr int bits = 22;
int R[bits][3100002];

class CCyclicalQuest {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N; cin >> N;
    vector<string> T(N); cin >> T;
    stringstream SS;

    SS << S << '$';
    for (string&t:T) SS << t << t << '$';
    string W = SS.str();
    int M = W.size();

    SuffixArray<int, true, false> SA(W);

    vector<int> Y(M, 0);
    for (int i = 0; i < M; ++i) Y[i] = (SA.S[i] < S.size());
    Fenwick<int> F(Y, 0);
    Fenwick<int> G(M, 0);

    for (int i = 0; i < M; ++i) R[0][i] = SA.LCP[i];
    for (int l = 0; l < bits-1; ++l) {
        for (int i = 0; i < M-(1<<l); ++i) R[l+1][i] = min(R[l][i], R[l][i + (1<<l)]);
    }

    int g = S.size()+1;
    for (string&t:T) {
        int ans = 0;
        int m = t.size();
        for (int i = 0; i < m; ++i) {
            int p = SA.I[g+i];
            for (int b = bits-1; b >= 0; --b) {
                if (p < M && R[b][p] >= m) p += 1<<b;
            }
            p = min(p, M-1);

            int l = SA.I[g+i];
            for (int b = bits-1; b >= 0; --b) {
                if (l >= (1<<b) && R[b][l-(1<<b)] >= m) l -= 1<<b;
            }
            if (G.range(l, p) == 0) ans += F.range(l, p);
            G.add(SA.I[g+i], 1);
        }

        for (int i = 0; i < m; ++i) G.add(SA.I[g+i], -1);
        cout << ans << '\n';

        g += m+m+1;
    }

}
};
