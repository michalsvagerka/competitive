#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    vector<bool> V;
    vector<int> P;
    vector<vector<pii>> E;

    bool test(int v, int s) {
        if (V[v]) return P[v] == s;
        V[v] = true;
        P[v] = s;
        for (pii&e:E[v]) {
            if (!test(e.x, s + e.y)) return false;
        }
        return true;
    }


    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        V = vector<bool>(N, false);
        P = vector<int>(N);
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int l,r,d; cin >> l >> r >> d;
            --l; --r;
            E[l].push_back({r,d});
            E[r].push_back({l,-d});
        }

        for (int i = 0; i < N; ++i) {
            if (!V[i] && !test(i, 0)) {
                cout << "No\n";
                return;
            }
        }

        cout << "Yes\n";
    }
};
