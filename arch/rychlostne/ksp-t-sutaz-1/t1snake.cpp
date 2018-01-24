#include "../l/lib.h"
// #include "../l/mod.h"

#define q(x) if (read(x)) return
// #define q(x) { if(!--t) { cerr << endl; return; } cerr << x; }

class snake {
public:
    int R,C;
    int l;

    bool read(char ch) {
        cout << ch << endl;
        string S; cin >> S;
        l = 0;
        if (S == "END") return true;
        for (int i = 0; i < C; ++i) if (S[i] == '.') l++;
        for (int r = 0; r < R - 1; ++r) {
            cin >> S;
            for (int i = 0; i < C; ++i) if (S[i] == '.') l++;
        }
        return false;
    }

    void solve(istream& cin, ostream& cout) {
        //int t = 50;

        cin >> R >> C;
        while (true) {
            int hr,hc;
            for (int r = 0; r < R; ++r) {
                string S; cin >> S;
                for (int c = 0; c < C; ++c) {
                    if (S[c] == '%') {
                        hr = r;
                        hc = c;
                    }
                }
            }
            if (hr != 1) {
                cout << "U" << endl;
            } else if (hc != 1) {
                cout << "L" << endl;
            } else break;
        }

        bool z = true;

        while (true) {
            q('R');
            for (int r = 0; r < R/2-2; r++) {
                for (int c = 0; c < C-4; ++c) q('R');
                q('D');
                for (int c = 0; c < C-4; ++c) q('L');
                q('D');
            }
            for (int c = 0; c < C-4; ++c) q('R');
            q('D');
            if (R%2==1) {
                for (int c = 0; c < C / 2 - 2; c++) {
                    q('D'); q('L'); q('U'); q('R');
                }

                q('D'); q('L');
                if (C%2 == 1) {
                    if (z) q('U');
                    q('L');
                    if (!z) q('U');
                    z = !z;
                    if (l == 0) { if(z)  q('R'); else q('D'); }
                } else {
                    q('U');
                }
            } else {
                for (int c = 0; c < C - 3; ++c) q('L');
                q('U');
            }
            for (int r = 0; r < R - 4; ++r) q('U');
        }

    }
};
