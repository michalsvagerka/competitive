#include "../l/lib.h"
// #include "../l/mod.h"

class Castle {
public:
    int N;
    vector<vector<pii>> E;

    struct Sol {
        double tot;
        int size;
        int len;
    };

    Sol solve(int u, int p) {
        vector<Sol> R;
        Sol C{0.0,0,0};
        C.size++;

        for (pii&e:E[u]) {
            if (e.x != p) {
                Sol z = solve(e.x, u);
                z.len += 2 * e.y;
                z.tot += e.y * z.size;

                C.size += z.size;
                C.len += z.len;
                C.tot += z.tot;

                R.push_back(z);
            }
        }

        sort(R.begin(),R.end(),[](const Sol&a, const Sol&b) {
            return ll(a.size) * b.len > ll(b.size) * a.len;
        });

        ll len = 0;
        for (Sol&r:R) {
            C.tot += len * r.size;
            len += r.len;
        }

        return C;
    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        --u;
        --v;
        E[u].push_back({v,t});
        E[v].push_back({u,t});
    }

    Sol S = solve(0, -1);
    cout << fixed << setprecision(12) << double(S.tot) / (N-1) << '\n';
//    cout << S.tot << ' ' << S.len << ' ' << S.size << endl;
}
};
