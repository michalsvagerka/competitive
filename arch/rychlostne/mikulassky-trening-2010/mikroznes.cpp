#include "../l/lib.h"
// #include "../l/mod.h"

class mikroznes {
public:
    vector<vector<int>> E, R, BE;
    vector<bool> L;
    vector<int> EP, A, V, C, Q;
    int N, M, T;
    static const int inf = 1<<24;

    inline int transition(int mask, int i) {
        int newMask = 0;
        for (int j = 0; j < N; ++j) {
            if ((mask & (1 << j)) && j != i) {
                newMask |= A[j];
            }
        }
        return newMask;
    }

    vector<int> test() {
        if (M != N-1) return {}; // not a cycle
        if (N == 1) return {0}; // single vertex
        if (N == 2) return {0,0}; // single edge

        // get leaves
        L.resize(N);
        for (int i = 0; i < N; ++i) L[i] = E[i].size() == 1;

        // get non-leaf edges
        R.clear(); R.resize(N);
        EP.clear();
        for (int i = 0; i < N; ++i) {
            if (!L[i]) {
                for (int v:E[i]) if (!L[v]) R[i].push_back(v);
                if (R[i].size() <= 1) EP.push_back(i);
            }
        }

//         a star
        if (EP.size() == 1) return {EP[0],EP[0]};

        if (EP.size() == 2) {
            // path with extra leaves
            vector<int> P;
            P.push_back(EP[0]);
            P.push_back(R[EP[0]][0]);
            int l = 2;
            while (R[P[l - 1]].size() == 2) {
                int n = R[P[l - 1]][0] + R[P[l - 1]][1] - P[l - 2];
                P.push_back(n);
                ++l;
            }

            for (int i = 0; i < l; ++i) P.push_back(P[l%2 == 0 ? l-1-i : i]);
            return P;
        }

        A.resize(N);
        for (int i = 0; i < N; ++i) {
            A[i] = 0;
            for (int u:E[i]) A[i] |= 1<<u;
        }

        int q = 1;
        Q[0] = (1<<N)-1;
        V[(1<<N)-1] = T;
        C[(1<<N)-1] = 0;
        for (int i = 0; i < q; ++i) {
            int mask = Q[i];
            if (mask == 0) { q = i; break; }
            for (int j = 0; j < N; ++j) {
                if (mask&(1<<j)) {
                    int newMask = transition(mask,j);
                    if (V[newMask] != T) {
                        V[newMask] = T;
                        C[newMask] = C[mask] + 1;
                        BE[newMask].clear();
                        BE[newMask].push_back(mask);
                        Q[q++] = newMask;
                    } else if (C[newMask] == C[mask] + 1) {
                        BE[newMask].push_back(mask);
                    }
                }
            }
        }

        if (V[0] != T) return {}; // path not found
        for (int i = 0; i < q; ++i) V[Q[i]] = inf;
        for (int i = q; i >= 0; --i) {
            if (V[Q[i]] == T) {
                for (int be:BE[Q[i]]) V[be] = T;
            }
        }

        vector<int> ret;
        int mask = (1<<N)-1;
        while (mask) {
            for (int i = 0; i < N; ++i) {
                int newMask = transition(mask, i);
                if (V[newMask] == T && C[newMask] == C[mask] + 1) {
                    ret.push_back(i);
                    mask = newMask;
                    break;
                }
            }
        }

        return ret;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> T;
        V = vector<int>(1<<21, T);
        C.resize(1<<21);
        Q.resize(1<<21);
        BE.resize(1<<21);
        while (T--) {
            cin >> N >> M;
            E.clear(); E.resize(N);
            for (int i = 0; i < M; ++i) {
                int a,b; cin >> a >> b;
                E[a].push_back(b);
                E[b].push_back(a);
            }

            auto ans = test();
            if (ans.empty()) {
                cout << "smola\n";
            } else {
                cout << ans.size() << ": " << ans;
            }
        }
    }
};
