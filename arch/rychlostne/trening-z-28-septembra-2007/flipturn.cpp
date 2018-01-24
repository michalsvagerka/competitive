#include "../l/lib.h"
// #include "../l/mod.h"

class flipturn {
public:
    bool ok(int a, int b, int c, int d, bool flipVert, bool flipHor, bool flipDiag) {
        int e = 1, f = 2, g = 3, h = 4;
        if (flipVert) {
            swap(e,f);
            swap(g,h);
        }
        if (flipHor) {
            swap(e,g);
            swap(f,h);
        }
        if (flipDiag) swap(f,g);
        return (a==e && b==f);
    }

    void solve(istream& cin, ostream& cout) {
        ui M,N; cin >> M >> N;
        vector2<char> C(M,N); cin >> C;
        string S; cin >> S;
        ui a = 1, b = 2, c = 3, d = 4;
        for (char s: S) {
            switch (s) {
                case 'H':
                    swap(a,c);
                    swap(b,d);
                    break;
                case 'V':
                    swap(a,b);
                    swap(c,d);
                    break;
                case '1':
                    swap(b,c);
                    break;
                case '2':
                    swap(a,d);
                    break;
                case 'B':
                case 'Y':
                    swap(a,d);
                    swap(b,c);
                    break;
                case 'A':
                case 'Z':
                    swap(c,d);
                    swap(b,d);
                    swap(a,b);
                    break;
                case 'C':
                case 'X':
                    swap(a,b);
                    swap(b,d);
                    swap(c,d);
                    break;
            }
        }


        for (bool flipVert:{true,false}) for (bool flipHor:{true,false}) for (bool flipDiag:{true,false}) {
                    if (!ok(a,b,c,d,flipVert,flipHor,flipDiag)) continue;
                    if (flipVert) {
                        for (auto &l:C)
                            reverse(l.begin(), l.end());
                    }


                    if (flipHor) {
                        reverse(C.begin(), C.end());
                    }


                    if (flipDiag) {
                        vector2<char> Z(N, M);
                        for (int r = 0; r < M; ++r) {
                            for (int c = 0; c < N; ++c) {
                                Z[c][r] = C[r][c];
                            }
                        }
                        swap(Z, C);
                        swap(M, N);
                    }

                    cout << M << ' ' << N << '\n';
                    for (auto &c: C) {
                        for (auto &cc:c) cout << cc;
                        cout << '\n';
                    }
                }
    }
};
