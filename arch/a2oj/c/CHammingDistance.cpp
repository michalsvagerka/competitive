#include "../l/lib.h"

class CHammingDistance {
public:
    void solve(istream &cin, ostream &cout) {
        vector<int> D(6);
        cin >> D;
        vector2<int> G(4, 4, 0);
        G[0][1] = G[1][0] = D[0];
        G[0][2] = G[2][0] = D[1];
        G[0][3] = G[3][0] = D[2];
        G[1][2] = G[2][1] = D[3];
        G[1][3] = G[3][1] = D[4];
        G[2][3] = G[3][2] = D[5];
        vector<int> Tot(4, 0);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                Tot[i] += G[i][j];
            }
        }
        vector<string> S(4);
        while (true) {
            vector<pii> TT;
            for (int i = 0; i < 4; ++i) TT.emplace_back(Tot[i], i);
            sort(TT.begin(), TT.end());
            if (TT[3].x == 0) {
                cout << S[0].size() << endl;
                for (string s: S) cout << s << endl;
                return;
            }
            if (TT[0].x == 0) {
                cout << "-1\n";
                return;
            }
            if (TT[3].x > TT[0].x) {
                if (TT[3].x == 2) {
                    cout << "-1\n";
                    return;
                }
                int j = TT[3].y;
                for (int i = 0; i < 4; ++i) {
                    S[i] += char('a'+(i==j));
                    if (i!=j) {
                        G[i][j] = --G[j][i];
                        Tot[i]--;
                    }
                }
                Tot[j] -= 3;
            } else {
                vector<pii> LO;
                for (int j = 1; j <= 3; ++j) LO.emplace_back(G[0][j], j);
                sort(LO.begin(),LO.end());
                int j = LO[0].y;
                int k = j==1 ? 2 : 1;
                int l = j==3 ? 2 : 3;
                if (G[0][k] == 0 || G[0][l] == 0 || G[j][k] == 0 || G[j][l] == 0) {
                    cout << "-1\n";
                    return;
                }

                G[0][k] = --G[k][0];
                G[0][l] = --G[l][0];
                G[j][k] = --G[k][j];
                G[j][l] = --G[l][j];
                for (int i = 0; i < 4; ++i) {
                    S[i] += char('a'+(i==0||i==j));
                    Tot[i] -= 2;
                }
            }
        }

    }
};
