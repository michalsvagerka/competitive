#include "../l/lib.h"

class CSkolemXORTree {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (__builtin_popcount(N) == 1) { cout << "No\n"; return; }
        vector<pii> E{{1,2},{2,3},{3,N+1},{N+1,N+2},{N+2,N+3}};
        for (int i = 4; i + 1 <= N; i+=2) {
            E.emplace_back(1, i);
            E.emplace_back(1, i+1);
            E.emplace_back(i, N+i+1);
            E.emplace_back(i+1, N+i);
        }
        if (N%2 == 0) {
            int k = 1;
            while (2*k <= N) k *= 2;
            E.emplace_back(k+1, N);
            E.emplace_back(N-k, 2*N);
        }
        
        cout << "Yes\n";
        for (pii e:E) cout << e.x << ' ' << e.y << '\n';
    }
};
