#include "../../../l/lib.h"
// #include "../l/mod.h"

class gridception {
public:
    struct Calc {

        int R,C;
        vector<string> P;
        int ans;

        int dfs(int r, int c, vector2<bool>&v) {
            if (r < 0 || r >= R || c < 0 || c >= C) return 0;
            if (!v[r][c]) return 0;
            v[r][c] = false;
            return 1 + dfs(r+1,c,v) + dfs(r-1,c,v) + dfs(r,c-1,v) + dfs(r,c+1,v);
        }

        void calc() {
            ans = 0;

            if (R == 1 && C == 1) {
                ans = 1;
                return;
            }

            vector<int> T(16, false);
            for (int r = 0; r < R-1; ++r) {
                for (int c = 0; c < C-1; ++c) {
                    int b = 0;
                    b |= (P[r][c]=='W');
                    b |= (P[r+1][c]=='W')<<1;
                    b |= (P[r][c+1]=='W')<<2;
                    b |= (P[r+1][c+1]=='W')<<3;
                    T[b] = true;
                }
            }

            for (int r = 0; r < R-1; ++r) {
                for (int c = 0; c < C; ++c) {
                    int b = 0;
                    b |= (P[r][c]=='W');
                    b |= (P[r+1][c]=='W')<<1;
                    b |= (b<<2);
                    T[b] = true;
                }
            }

            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C-1; ++c) {
                    int b = 0;
                    b |= (P[r][c]=='W');
                    b |= (P[r][c+1]=='W')<<2;
                    b |= (b<<1);
                    T[b] = true;
                }
            }

            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    T[(P[r][c]=='W') ? 15 : 0] = true;
                }
            }

            for (int r = 0; r <= R; ++r) {
                for (int c = 0; c <= C; ++c) {
                    for (int i = 0; i < 16; ++i) {
                        if (T[i]) {
                            vector2<bool> F(R,C,false);
                            for (int rr = 0; rr < R; ++rr) {
                                for (int cc = 0; cc < C; ++cc) {
                                    int j = (rr > r) | ((cc > c)<<1);
                                    F[rr][cc] = ((i&(1<<j))==(1<<j)) == (P[rr][cc]=='W');
                                }
                            }

//                            cerr << F;

                            for (int rr = 0; rr < R; ++rr) {
                                for (int cc = 0; cc < C; ++cc) {
                                    ans = max(ans, dfs(rr,cc,F));
                                }
                            }
                        }
                    }
                }
            }
        }

        void read(istream& cin) {
            cin >> R >> C;
            P.resize(R);
            cin >> P;
        }

        void write(ostream &cout) {
            cout << ans << '\n';
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            Calc c;
            c.read(cin);
            c.calc();
            cout << "Case #" << t << ": ";
            c.write(cout);
        }
    }
};
