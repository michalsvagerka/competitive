#include "../l/lib.h"
// #include "../l/mod.h"

vector<string> T{
        "pconinbfjhjmagcj",
        "gaonlefmkbihfkoc",
        "glmankjljmehkedj",
        "cgknlcabbehehhka",
        "bijnpompdgdnpnid",
        "aepoiamohejpgmlo",
        "bddbmjdngdcpeeja",
        "kiocldhhakhihnfg",
        "plehbonfjkgligfp",
        "pkfjkmmkcneolfek",
        "lckdpnailpjefbli",
        "mfjabdhllpmefmlc",
        "hcgffiegcnpgeami",
        "phdafbfbiahjkolc",
        "oacdbdbondfgmonc",
        "idcoogajpiimbgkb"
};

class P5 {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        vector3<ll> D(N+1, N+1, 16, 0);
        for (int i = 0; i < N; ++i) D[1][i][S[i]-'a'] = 1;
        for (int l = 2; l <= N; ++l) {
            for (int i = 0; i + l <= N; ++i) {
                for (int j = 0; j < 16; ++j) {
                    for (int k = 0; k < 16; ++k) {
                        int r = T[j][k]-'a';
                        for (int m = 1; m < l; ++m) {
                            D[l][i][r] += D[m][i][j] * D[l-m][i+m][k];
                        }
                    }
                }
            }
        }

        cout << D;
        
        ll ans = 0;
        for (int i = 1; i < N; ++i) {
            for (int j = 1; i + j < N; ++j) {
                for (int k = 1; i + j + k < N; ++k) {
                    ans += D[i][0][10] * D[j][i][0] * D[k][j+i][5] * D[N-i-j-k][i+j+k][4];
                }
            }
        }
        cout << ans << '\n';
    }
};
