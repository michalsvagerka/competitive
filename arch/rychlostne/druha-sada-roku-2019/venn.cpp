#include "../l/lib.h"

class venn {
public:
    void colour(int r, int c, vector<vector<int>> &v) {
        if (r == 50 || c == 50 || c == -1 || r == -1) return;
        if (v[r][c] == 0) return;
        v[r][c] = 0;
        colour(r+1,c,v);
        colour(r,c+1,v);
        colour(r,c-1,v);
        colour(r-1,c,v);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << "2 2\n0 0\n1 1\n";
            return;
        }
        
        vector2<int> S(50, 50, -1);
        int X = (1<<N)-1;

        for (int i = 0; i < 50; ++i) S[i][0] = X;
        for (int i = 0; i < 50; ++i) S[i][49] = 0;
        int h = 1;
        for (int i = 0; i < 50; ++i) {
            for (int j = 1; j < 49; ++j) {
                if (i % 4 == 0) {
                    S[i][j] = X;
                } else if (i % 4 == 2) {
                    S[i][j] = 0;
                } else {
                    S[i][j] = h;
                    h++;
                    if (h == 1) h = 0;
                    if (h == X) h = 0;
                }
            }
        }
//
//
        for (int i = 0; i < (1<<N); ++i) {
            auto T = S;
            for (int j = 0; j < 50; ++j) {
                for (int k = 0; k < 50; ++k) {
                    T[j][k] = (S[j][k] & i) == i;
                }
            }

            int cnt = 0;
            for (int j = 0; j < 50; ++j) {
                for (int k = 0; k < 50; ++k) {
                    if (T[j][k]) {
                        colour(j,k,T);
                        cnt++;
                    }
                }
            }
            if (cnt != 1) {
                cout << "FailA " << i << ' ' << cnt << endl;
                return;
            }
        }


        for (int i = 0; i < (1<<N); ++i) {
            auto T = S;
            for (int j = 0; j < 50; ++j) {
                for (int k = 0; k < 50; ++k) {
                    T[j][k] = S[j][k] == i;
                }
            }

            int cnt = 0;
            for (int j = 0; j < 50; ++j) {
                for (int k = 0; k < 50; ++k) {
                    if (T[j][k]) {
                        colour(j,k,T);
                        cnt++;
                    }
                }
            }
            if (cnt != 1) {
                cout << "FailB " << i << ' ' << cnt << endl;
                return;
            }
        }



        cout << "50 50\n";
        for (auto&s:S) cout << s;
    }
};
