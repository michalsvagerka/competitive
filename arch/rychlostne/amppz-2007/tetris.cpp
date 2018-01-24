#include "../l/lib.h"
#include "../l/matrix.h"
#include "../l/mod.h"

class tetris {
public:
    vector<vector<ui>> Q;

    void solve(ui mask, Matrix<Field<1000000>>::Row DP) {
        for (int i = 3; i >= 0; --i) {
            if ((mask & (1<<i)) == 0) {
                for (ui piece: Q[3-i]) {
                    if ((mask & piece) == 0) {
                        solve(mask | piece, DP);
                    }
                }
                return;
            }
        }

        DP[mask>>4]++;
    }

    void solve(istream& cin, ostream& cout) {
        Q = {
                {0x8c8,0x4e,             0x88c,0x2e,0xe8,        0x6c,        0xe,0x888,  0x8e,0x44c,0xc88,       0x4c8,      0xcc},
                {0x464,0x27,0x4c4,0xe4,  0x446,0x17,0x74,0xc44,  0x36,0x8c4,  0x7,0x444,  0x47,0x226,0x644,       0x264,0xc6, 0x66},
                {0x232,     0x262,0x72,  0x223,          0x622,       0x462,      0x222,       0x113,0x322,0xe2,  0x132,0x63, 0x33},
                {           0x131,                       0x311,       0x231,      0x111,                   0x71                   }
        };

        Matrix<Field<1000000>> DP(256,256);
        for (ui q = 0; q < 256; ++q) {
            solve(q, DP[q]);
        }

        vector<Matrix<Field<1000000>>> Z;
        Z.push_back(DP.transposed());
        for (ui p = 1; p < 30; ++p) Z.push_back(Z[p-1] * Z[p-1]);

        ui T; cin >> T;
        for (ui t = 0; t < T; ++t) {
            ui N; cin >> N;
            string s; cin >> s;
            ui mask = 0;
            for (ui i = 0; i < 4; ++i) {
                if (s[i] == '*') mask |= 1<<i;
            }

            vector<Field<1000000>> V(256,0);
            V[mask] = 1;

            for (ui i = 0; i < 30; ++i) {
                if (N&(1<<i)) {
                    V = Z[i] * V;
                }
            }

            cout << V[0] << '\n';

        }
    }
};

//02468ace
//01234567