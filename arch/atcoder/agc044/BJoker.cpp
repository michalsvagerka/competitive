#include "../l/lib.h"

class BJoker {
public:
    int N;
    vector<vector<int>> Cost;
    vector<vector<bool>> Occ;

    void dfs(int x, int y, int c) {
        if (x < 0 || x >= N || y < 0 || y >= N) return;
        if (Cost[x][y] <= c) return;
        Cost[x][y] = c;
        c += Occ[x][y];
        dfs(x-1,y,c);
        dfs(x+1,y,c);
        dfs(x,y-1,c);
        dfs(x,y+1,c);
    }

    void solve(istream& cin, ostream& cout) {
         cin >> N;
        vector<int> P(N*N); cin >> P;
        for (int &p: P) --p;

        Cost = vector2<int>(N, N, N);
        Occ = vector2<bool>(N, N, true);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                Cost[i][j] = min(Cost[i][j], i);
                Cost[i][j] = min(Cost[i][j], j);
                Cost[i][j] = min(Cost[i][j], N-i-1);
                Cost[i][j] = min(Cost[i][j], N-j-1);
            }
        }

        ll ans = 0;
        for (int i = 0; i < N*N; ++i) {
            int a = P[i]%N;
            int b = P[i]/N;
            int c = Cost[a][b];
            ans += c;
            Occ[a][b] = false;
            Cost[a][b] = N;
            dfs(a,b,c);
        }
        cout << ans << '\n';
    }
};
