#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    vector<set<int>> I;
    set<int> H;

    void add(int j, int k) {
        auto it = I[j].upper_bound(k);
        if (it != I[j].end()) H.insert(*it);
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> W(M);
        for (int i = M-1; i >= 0; --i) {
            cin >> W[i].x >> W[i].y;
            W[i].x--; W[i].y--;
        }

        I.resize(N);
        for (int i = 0; i < M; ++i) {
            I[W[i].x].insert(i);
            I[W[i].y].insert(i);
        }

        vector<bitset<400>> D(N);
        for (int i = 0; i < N; ++i) {
            D[i][i] = true;
            H.clear();
            add(i, -1);

            bool ok = true;
            while (!H.empty() && ok) {
                int k = *H.begin();
                H.erase(H.begin());
                if (D[i][W[k].x] && D[i][W[k].y]) {
                    ok = false;
                } else {
                    D[i][W[k].x] = D[i][W[k].y] = true;
                    add(W[k].x, k);
                    add(W[k].y, k);
                }
            }

            if (!ok) D[i].set();
        }


        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                ans += (D[i] & D[j]).none();
            }
        }

        cout << ans << endl;
    }
};
