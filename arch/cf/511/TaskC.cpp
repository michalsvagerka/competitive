#include "../l/lib.h"
 #include "../l/mod.h"

class TaskC {
public:
    vector<ll> SUMS;
    vector<vector<int>> E;
    vector<int> A;
    ll dfs(int u, int p) {
        ll s = A[u];
        for (int v : E[u]) {
            if (v != p) s += dfs(v, u);
        }
        return SUMS[u] = s;
    }

void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    A.resize(N);
    cin >> A;
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int p;
        cin >> p;
        E[i+1].push_back(p-1);
        E[p-1].push_back(i+1);
    }
    ll s = 0;
    for (int a:A) s += a;
    SUMS.resize(N);
    dfs(0, -1);

    vector<int> Z(N+1, 0);
    for (ll x:SUMS) {
        ll g = gcd(x, s);
        if (s/g <= N) {
            Z[s/g]++;
        }
    }

    for (int i = N; i > 0; --i) {
        for (int j = 2*i; j <= N; j += i) {
            Z[j] += Z[i];
        }
    }

    vector<FieldMod> Pos(N+1, 0);
    for (int i = N; i > 0; --i) {
        if ((s % i == 0) && Z[i] == i) {
            Pos[i] = 1;
            for (int j = 2*i; j <= N; j += i) {
                Pos[i] += Pos[j];
            }
        }
    }
    
    cout << Pos[1] << '\n';
}
};
