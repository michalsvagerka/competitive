#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class TaskF {
public:
    int N, R;
    vector<FieldMod> I,P,Q;
    vector<vector<int>> E;
    vector<vector<FieldMod>> D;

    void dfs(int u, int p) {
        D[u][0] = 1;
        for (int v:E[u]) {
            if (v != p) {
                dfs(v, u);
                P[0] = Q[0] = 0;
                for (int i = 0; i < N; ++i) {
                    P[i+1] = P[i] + D[u][i];
                    Q[i+1] = Q[i] + D[v][i];
                }

                for (int i = 0; i < N; ++i) {
                    D[u][i] = P[i+1] * Q[i+1] - P[i] * Q[i];
                }
            }
        }

        for (int i = 1; i < N; ++i) {
            D[u][i] += D[u][i-1];
        }
    }

    FieldMod choose(int A, int B) {
        FieldMod ans = 1;
        for (int i = 0; i < B; ++i) {
            ans *= FieldMod{A-i};
        }
        return ans * I[B];
    }


void solve(istream& cin, ostream& cout) {
    cin >> N >> R;
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int p; cin >> p;
        --p;
        E[p].push_back(i+1);
    }
    auto F = FieldMod::fact(N);
    I = FieldMod::invfact(N+1);
    D = vector2<FieldMod>(N,N,0);
    P.resize(N+1); Q.resize(N+1);

    dfs(0, -1);
    int Z = min(R,N);
    FieldMod ans = 0;


    for (int i = 1; i <= Z; ++i) {
        FieldMod x = 0;
        for (int j = 1; j <= i; ++j) {
            FieldMod y = D[0][j-1] * F[i-1] * I[j-1] * I[i-j];
            if ((j-i)%2==0) x += y; else x -= y;
        }
        ans += x * choose(R,i);
    }

    cout << ans << endl;


}
};
