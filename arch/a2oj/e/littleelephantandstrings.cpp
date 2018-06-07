#include "../../../l/lib.h"
#include "../../../l/suffixarray.h"

class littleelephantandstrings {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<string> S(N); cin >> S;
        vector<int> I, End;
        stringstream SS;
        int M = 0;
        for (int i = 0; i < N; ++i) {
            SS << S[i] << '$';
            M += S[i].size() + 1;
            End.push_back(M);
            for (int k = 0; k < S[i].size(); ++k) I.push_back(i);
            I.push_back(N);
        }

        SuffixArray<int, true, true> SA(SS.str());

        vector<int> Orig;
        for (int i = 0; i < M; ++i) Orig.push_back(I[SA.S[i]]);

        vector<int> C(N+1, 0), E;
        int W = 0; C[N] = 1;
        int e = 0;
        for (int b = 0; b < M; ++b) {
            while (e < M && W < K) if (!C[Orig[e++]]++) W++;
            E.push_back(W==K?e-1:M);
            if (!--C[Orig[b]]) W--;
        }


        vector<ll> Ans(N, 0);
        for (int i = 0; i < M; ++i) {
            // fuck off end of strings
            if (Orig[i] == N) continue;

            // find largest length y such that string starting here with length y has k distinct occurrences
            int k = bsh(0, (int)S[Orig[i]].size(), [&](int y) {
                // find the maximum interval (l,r) for which LCP(l,r) >= y
                int l = SA.LCP[i-1] >= y ? bsl(0, i-1, [&](int x) { return SA.lcp(SA.S[x], SA.S[i]) >= y; }) : i;
                int r = i < M-1 && SA.LCP[i] >= y ? bsh(i+1, M-1, [&](int x) { return SA.lcp(SA.S[i], SA.S[x]) >= y; }) : i;
                return E[l] <= r; // [l,E(l)) has exactly k distinct source strings, while [l,E(l)-1) does not
            });

            // if the match goes past the string end, cut it
            k = min(k, End[Orig[i]] - SA.S[i] - 1);

            Ans[Orig[i]] += max(0,k);
        }
        cout << Ans;
    }
};
