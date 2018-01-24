#include "../l/lib.h"
// #include "../l/mod.h"

class squares {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            vector<pii> V(N);
            set<pii> S;
            for (int i = 0; i < N; ++i) {
                cin >> V[i].x >> V[i].y;
                S.insert(V[i]);
            }

            int ans = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i==j) continue;
                    int dx = V[j].x - V[i].x;
                    int dy = V[j].y - V[i].y;

                    if (S.find({V[i].x + dy, V[i].y - dx}) != S.end()
                        && S.find({V[j].x + dy, V[j].y - dx}) != S.end()) ++ans;
                }
            }

            cout << ans/4 << endl;
            cin >> N;
        }
    }
};
