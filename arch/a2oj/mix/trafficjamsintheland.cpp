#include "../../../l/lib.h"
// #include "../l/mod.h"

class trafficjamsintheland {
public:
    vector<vector<int>> L,Z;

    void updateOne(int j) {
        for (int t = 0; t < 60; ++t) L[j][t] = L[2*j][t] + L[2*j+1][(t+L[2*j][t])%60];
    }

    void updateAll(int j) {
        while (j != 1) {
            j /= 2;
            updateOne(j);
        }
    }

    int find(int i, int l, int r, int x, int y, int t) {
        if (x <= l && y >= r) return t + L[i][t%60];
        if (x >= r || y <= l) return t;
        int m = (l+r)/2;
        t = find(2*i, l, m, x, y, t);
        return find(2*i+1, m, r, x, y, t);
    }

    void solve(istream& cin, ostream& cout) {
        Z = vector2<int>(7,60,1);
        for (int i = 2; i <= 6; ++i) for (int j = 0; j < 60; j+=i) Z[i][j]++;
        
        int N; cin >> N;
        int M = 1<<logceil(N);
        L = vector2<int>(2*M, 60, 0);
        for (int i = 0; i < N; ++i) {
            int a; cin >> a;
            L[M+i] = Z[a];
        }

        for (int t = M-1; t >= 1; --t) updateOne(t);

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            char t; cin >> t;
            if (t == 'A') {
                int x, y; cin >> x >> y;
                --x; --y;
                cout << find(1, 0, M, x, y, 0) << '\n';
            } else {
                int x,y; cin >> x >> y;
                --x;
                L[M+x] = Z[y];
                updateAll(M+x);
            }
        }
    }
};
