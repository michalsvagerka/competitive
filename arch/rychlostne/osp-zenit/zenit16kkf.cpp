#include "../l/lib.h"

class zenit16kkf {
public:

    void fill(const vector<string>& P, vector<string>& C, int d, int G, int S, int a, int b) {
        if (d == G) {
            C[a][b] = '#';
        } else {
            for (int i = 0; i < S; ++i) {
                for (int j = 0; j < S; ++j) {
                    if (P[i][j] == '#') {
                        fill(P, C, d+1, G, S, a*S+i, b*S+j);
                    }
                }
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int S, G;
        cin >> S >> G;
        string junk;
        getline(cin, junk);
        vector<string> P(S);
        for (int i = 0; i < S; ++i) {
            getline(cin, P[i]);
        }

        int W = 1;
        for (int i = 0; i < G; ++i) W *= S;
        vector<string> CH(W, string(W, ' '));

        fill(P, CH, 0, G, S, 0, 0);

        for (auto ch: CH) {
            for (int i = 0; i < W; ++i) {
                cout << ch[i] << " \n"[i==W-1];
            }
        }
    }
};
