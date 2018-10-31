#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<string> S(N); cin >> S;
    vector3<bool> A(4, N, M, false);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            switch (S[i][j]) {
                case '+': A[0][i][j] = A[1][i][j] = A[2][i][j] = A[3][i][j] = true; break;
                case 'L': A[1][i][j] = A[2][i][j] = A[3][i][j] = true; break;
                case 'U': A[0][i][j] = A[2][i][j] = A[3][i][j] = true; break;
                case 'R': A[0][i][j] = A[1][i][j] = A[3][i][j] = true; break;
                case 'D': A[0][i][j] = A[1][i][j] = A[2][i][j] = true; break;
                case '-': A[0][i][j] = A[2][i][j] = true; break;
                case '|': A[1][i][j] = A[3][i][j] = true; break;
                case '<': A[0][i][j] = true; break;
                case '^': A[1][i][j] = true; break;
                case '>': A[2][i][j] = true; break;
                case 'v': A[3][i][j] = true; break;
            }
        }
    }
    int XT, YT; cin >> XT >> YT; --XT; --YT;
    int XS, YS; cin >> XS >> YS; --XS; --YS;

    vector3<int> D(4, N, M, 1e9);
    vector<pair<int,pii>> H;
    H.push_back({0,{XT,YT}});
    D[0][XT][YT] = 0;

    for (int i = 0; i < H.size(); ++i) {
        auto h = H[i];
        int x = h.y.x, y = h.y.y, t = h.x, d = D[t][x][y];
        if (x > 0 && d + 1 < D[t][x-1][y] && A[(t+1)&3][x][y] && A[(t+3)&3][x-1][y]) {
            D[t][x-1][y] = d + 1;
            H.push_back({t, {x-1,y}});
        }
        if (x < N-1 && d + 1 < D[t][x+1][y] && A[(t+3)&3][x][y] && A[(t+1)&3][x+1][y]) {
            D[t][x+1][y] = d + 1;
            H.push_back({t, {x+1,y}});
        }
        if (y > 0 && d + 1 < D[t][x][y-1] && A[(t)&3][x][y] && A[(t+2)&3][x][y-1]) {
            D[t][x][y-1] = d + 1;
            H.push_back({t, {x,y-1}});
        }
        if (y < M-1 && d + 1 < D[t][x][y+1] && A[(t+2)&3][x][y] && A[(t)&3][x][y+1]) {
            D[t][x][y+1] = d + 1;
            H.push_back({t, {x,y+1}});
        }
        if (d + 1 < D[(t+3)&3][x][y]) {
            D[(t+3)&3][x][y] = d+1;
            H.push_back({(t+3)&3, {x,y}});
        }
    }
    
    int ans = 1e9;
    for (int i = 0; i < 4; ++i) {
        ans = min(ans, D[i][XS][YS]);
    }
    if (ans == 1e9) ans = -1;
    cout << ans << endl;
}
};
