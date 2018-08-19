#include "../l/lib.h"
// #include "../l/mod.h"

class ColorTheCarpet {
public:
void solve(istream& cin, ostream& cout) {
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> S(2*H-1); cin >> S;
    if (K == 1) {
        int e = 0, n = 0;
        for (string&s:S) for (char c:s) if (c == 'E') e++; else n++;
        if (n * 3 <= e) {
            cout << "YES\n";
            vector<int> Ans(W, 1);
            for (int i = 0; i < H; ++i) {
                cout << Ans;
            }
        } else {
            cout << "NO\n";
        }
        return;
    }

    cout << "YES\n";

    bool sw = false;
    if (H > W) {
        vector<string> T(2 * W - 1);
        for (int c = 0; c < W; ++c) {
            T[2 * c] = string(H - 1, ' ');
            for (int r = 0; r < H - 1; ++r) {
                T[2 * c][r] = S[2 * r + 1][c];
            }
            if (c != W - 1) {
                T[2 * c + 1] = string(H, ' ');
                for (int r = 0; r < H; ++r) {
                    T[2 * c + 1][r] = S[2 * r][c];
                }
            }
        }

        sw = true;
        swap(T,S);
        swap(H,W);
    }

    vector2<int> Ans(H,W,0);
    for (int r = 0; r < H; ++r) {
        Ans[r][0] = 0;
        for (int c = 1; c < W; ++c) {
            Ans[r][c] = Ans[r][c-1] ^ (S[2*r][c-1]=='N');
        }
        if (r != 0) {
            int a = 0;
            for (int c = 0; c < W; ++c) {
                a += Ans[r][c] == (Ans[r-1][c] ^ (S[2*r-1][c]=='N'));
            }
            if (a * 2 < W) {
                for (int c = 0; c < W; ++c) Ans[r][c] = !Ans[r][c];
            }
        }
    }

    if (sw) {
        vector2<int> Sw(W,H,0);
        for (int i = 0; i < W; ++i) {
            for (int j = 0; j < H; ++j) {
                Sw[i][j] = Ans[j][i];
            }
        }
        swap(Sw, Ans);
    }

    for (auto&ans:Ans) {
        for (auto&i:ans) i++;
        cout << ans;
    }
}
};
