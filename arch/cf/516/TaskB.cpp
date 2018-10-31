#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    int R, C; cin >> R >> C;
    int X, Y; cin >> X >> Y;
    --R; --C;
    vector<string> S(N); cin >> S;

    constexpr int mx = 1e9;
    vector2<int> D(N, M, mx);
    vector<pii> Cur, Next;
    D[R][C] = 0;
    Cur.push_back({R,C});
    int left = 0;
    while (!Cur.empty() || !Next.empty()) {
        for (int i = 0; i < Cur.size(); ++i) {
            auto c = Cur[i];
            if (S[c.x][c.y] == '*') continue;
            if (D[c.x][c.y] != left) continue;
            if (c.x > 0 && D[c.x-1][c.y] > left) {
                D[c.x-1][c.y] = left;
                Cur.push_back({c.x-1,c.y});
            }
            if (c.x < N-1 && D[c.x+1][c.y] > left) {
                D[c.x+1][c.y] = left;
                Cur.push_back({c.x+1,c.y});
            }
            if (c.y > 0 && D[c.x][c.y-1] > left + 1) {
                D[c.x][c.y-1] = left + 1;
                Next.push_back({c.x,c.y-1});
            }
            if (c.y < M-1 && D[c.x][c.y+1] > left) {
                D[c.x][c.y+1] = left;
                Cur.push_back({c.x,c.y+1});
            }
        }
        swap(Next,Cur);
        Next.clear();
        left++;
    }

    
    int ans = 0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (D[r][c] != mx && S[r][c] != '*') {
                int ll = D[r][c];
                int rr = D[r][c] + c - C;
                if (ll <= X && rr <= Y) ans++;
            }
        }
    }
    cout << ans << endl;
}
};
