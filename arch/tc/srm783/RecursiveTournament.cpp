#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;
int E[23],ER[23];

class RecursiveTournament {
public:
    int cnt(int N, int e) {
        int MOD = 998244353-1;
        ll p = N;
        ll r = 1;
        while (e) {
            if (e&1) ( r *= p ) %= MOD;
            (p *= p) %= MOD;
            e >>= 1;
        }
        return (int)r;
    }
    int count(vector <string> graph, int k) {
        int N = graph.size();

        for (int i=0; i<N; ++i) E[i] = ER[i] = 0;
        for (int l = 0; l < N; ++l) {
            for (int k = 0; k < N; ++k) {
                E[l] |= (graph[l][k] == 'Y')<<k;
                ER[k] |= (graph[l][k] == 'Y')<<l;
            }
        }
        vector<int> SCC(N+1, 0);
        for (int m = 0; m < (1<<N); ++m) {
            int M = __builtin_popcount(m);
            if (M >= 3) {
                int lo = 0;
                while ((m&1<<lo) == 0) ++lo;
                int s = 1<<lo, oldS = 0;
                while (oldS != s) {
                    int g = (s^oldS)&m;
                    oldS = s;
                    while (g) {
                        int h = __builtin_ctz(g);
                        s |= E[h];
                        g ^= 1<<h;
                    }
                }
                int t = 1<<lo, oldT = 0;
                while (oldT != t) {
                    int g = (t^oldT)&m;
                    oldT = t;
                    while (g) {
                        int h = __builtin_ctz(g);
                        t |= ER[h];
                        g ^= 1<<h;
                    }
                }
                SCC[M] += (t&m)==m && (s&m) == m;
            }
        }

        int K = k;
        FF ans = FF{N}.pow(K);
        for (int i = 0; i < K; ++i) {
            for (int j = 3; j <= N; ++j) {
                ans += SCC[j] * FF{N}.pow(K-1-i) * (FF{2}.pow(cnt(N,i)) - 1).pow(j);
            }
        }
        return (ui)ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << count({ "NYN", "NNY", "YNN" },2) << '\n';
        cout << count({ "NYY", "NNY", "NNN" },2) << '\n';
        cout << count({ "NYN", "NNY", "YNN" },1) << '\n';
        cout << count({ "NYYYNNYNNYYNNYYYYYNNYNN", "NNYNYYNYYNNNYNYNYNNNNYY", "NNNNYNNNNYNYYNYYNYYNYNN", "NYYNYNNNYNNYYYNYYYNNYYN", "YNNNNNYYNYNNYYNNYNYNYYY", "YNYYYNNNYNYNYNYNNYNYNYN", "NYYYNYNNNYYNNNNYNNNNYNN", "YNYYNYYNYYYNYNYYYNYNNYY", "YNYNYNYNNYYYNYNYNYYYNYN", "NYNYNYNNNNYNYYYNNYYYNYN", "NYYYYNNNNNNNNYNYYNNYNYN", "YYNNYYYYNYYNNYYYYNYYYNY", "YNNNNNYNYNYYNNNNYNYNYNY", "NYYNNYYYNNNNYNYNNNNYNYN", "NNNYYNYNYNYNYNNYNNNYNNY", "NYNNYYNNNYNNYYNNYNYYNYN", "NNYNNYYNYYNNNYYNNNYNNNN", "NYNNYNYYNNYYYYYYYNYYYNN", "YYNYNYYNNNYNNYYNNNNNYNY", "YYYYYNYYNNNNYNNNYNYNYNN", "NYNNNYNYYYYNNYYYYNNNNNY", "YNYNNNYNNNNYYNYNYYYYYNY", "YNYYNYYNYYYNNYNYYYNYNNN" },1000) << '\n';
    }
};

/*
 * 1
0
1
 483387
1990213
 */