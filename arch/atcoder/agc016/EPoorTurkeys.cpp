#include "../l/lib.h"

class EPoorTurkeys {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> V(M); cin >> V;
        for (pii&v: V) { v.x--; v.y--; }
        vector<bitset<400>> X(N);
        for (pii v: V) {
            int a = v.x, b = v.y;
            if ((X[a] & X[b]).any() || X[a][b] || X[b][a] || X[a][a] || X[b][b]) {
                X[a].set(a);
                X[b].set(b);
            } else {
                X[a] = X[b] = X[a] | X[b];
                X[a].set(b);
                X[b].set(a);
            }
        }

        int ans = 0;
        for (int a = 0; a < N; ++a) {
            for (int b = a+1; b < N; ++b) {
                if ((X[a] & X[b]).none() && !X[a][a] && !X[a][b] && !X[b][a] && !X[b][b]) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
};
