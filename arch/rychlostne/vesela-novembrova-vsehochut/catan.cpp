#include "../l/lib.h"
// #include "../l/mod.h"

class catan {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        map<char,pii> M{{'A',{2,0}},
                        {'B',{1,1}},{'C',{3,1}},
                        {'D',{0,2}},{'E',{2,2}},{'F',{4,2}},
                        {'G',{1,3}},{'H',{3,3}},
                        {'I',{0,4}},{'J',{2,4}},{'K',{4,4}},
                        {'L',{1,5}},{'M',{3,5}},
                        {'N',{0,6}},{'O',{2,6}},{'P',{4,6}},
                        {'Q',{1,7}},{'R',{3,7}},
                        {'S',{2,8}},
        };
        vector<int> L{2,4,6,6,6,6,6,6,6,4,2};
        int K = L.size();
        vector<int> DX{1,1,1,0,0,0}, DY{0,1,2,2,1,0};
        vector<int> Z(K, 0);
        for (int i = 0; i < N; ++i) {
            char c; int j;
            cin >> c >> j;
            int x = M[c].x + DX[j-1], y = M[c].y + DY[j-1];
            Z[y] |= 1<<x;
        }

        vector2<int> Q(K,1<<6,false);
        for (int i = 0; i < K; ++i) {
            int base = (1<<2)|(1<<3);
            if (L[i] >= 4) base |= (1<<1)|(1<<4);
            if (L[i] == 6) base |= (1<<0)|(1<<5);
            for (int j = 0; j < (1<<6); ++j) {
                bool ok = (j&base) == j;
                for (int k = i%2; k < 6; k+=2) {
                    ok &= ((j&(3<<k)) != (3<<k));
                }
                Q[i][j] = ok & ((j&Z[i])==Z[i]);
            }
        }

        vector2<ll> DP(K + 1, 1 << 6, 0);
        DP[0][0] = 1;
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < (1<<6); ++j) {
                if (!DP[i][j]) continue;
                for (int k = 0; k < (1<<6); ++k) {
                    if ((j&k) == 0 && Q[i][k]) {
                        DP[i+1][k] += DP[i][j];
                    }
                }
            }
        }

        ll ans = 0;
        for (int j = 0; j < (1<<6); ++j) {
            ans += DP[K][j];
        }
        cout << ans << endl;
    }
};
