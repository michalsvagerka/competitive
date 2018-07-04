#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    int N;
    vector<vector<pii>> E;
    vector<int> Ans, S;

    int size(int u) {
        S[u] = 1;
        for (pii v:E[u]) S[u] += size(v.x);
        return S[u];
    }


    void fill(int u, int depth, int mask, unordered_map<int,int>&X) {
        X[mask] = depth;
        for (pii v:E[u]) {
            unordered_map<int,int> Z;
            fill(v.x, depth+1, mask ^ (1<<v.y), Z);
            if (X.size() < Z.size()) swap(X,Z);
            for (pii z:Z) {
                auto it = X.find(z.x);
                if (it != X.end()) Ans[u] = max(Ans[u], it->y + z.y - 2*depth);

                for (int i = 0; i < 22; ++i) {
                    auto it = X.find(z.x ^ (1<<i));
                    if (it != X.end()) Ans[u] = max(Ans[u], it->y + z.y - 2*depth);
                }
            }

            for (pii z:Z) {
                X[z.x] = max(X[z.x], z.y);
            }
            Ans[u] = max(Ans[u], Ans[v.x]);
        }
    }


void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    S.resize(N);
    Ans = vector<int>(N, 0);
    for (int i = 1; i < N; ++i) {
        int p; char c;
        cin >> p >> c;
        --p;
        E[p].push_back({i, c-'a'});
    }

    size(0);
    for (int i = 0; i < N; ++i) {
        sort(E[i].begin(),E[i].end(),[&](pii a, pii b) { return S[a.x] < S[b.x]; });
    }

    unordered_map<int,int> X;
    fill(0, 0, 0, X);
    cout << Ans;
}
};
