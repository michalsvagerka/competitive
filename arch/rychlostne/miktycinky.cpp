#include "../../l/lib.h"
// #include "../l/mod.h"

class miktycinky {
public:
    int R,C;
    vector<string> T;
    void fill(int r, int c, char q, char z) {
        if (r < 0 || r >= R || c < 0 || c >= C || T[r][c] != q) return;
        T[r][c] = z;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                fill(r+dr,c+dc,q,z);
            }
        }
    }


    void solve(istream& cin, ostream& cout) {
        cin >> R >> C;
        T.resize(R);
        cin >> T;
        int l = 0, o = 0;
        for (int r = 0; r < R; ++r) {
            fill(r,0,'.','_');
            fill(r,C-1,'.','_');
        }

        for (int c = 0; c < C; ++c) {
            fill(0,c,'.','_');
            fill(R-1,c,'.','_');
        }

        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (T[r][c] == '#') {
                    ++l;
                    fill(r,c,'#','_');
                } else if (T[r][c] == '.') {
                    ++o;
                    fill(r,c,'.','_');
                }
            }
        }

        if (l == 4 && o == 2) cout << "MARX\n";
        else if (l == 8 && o == 0) cout << "STICKEYS\n";
        else if (l == 6 && o == 3) cout << "BOUNCY\n";
        else if (l == 7 && o == 1) cout << "KITECAT\n";
        else if (l == 8 && o == 3) cout << "MILKY BAY\n";
        else { int *p = 0; cout << *p << endl; }
    }
};
