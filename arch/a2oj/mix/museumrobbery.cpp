#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class museumrobbery {
public:
    vector<pair<set<int>,FieldMod>> S;
    int N, K, TT;
    vector<pii> E;

    void put(int i, int l, int r, int u, int v, int j) {
        if (u >= r || v <= l) return;
        else if (u <= l && v >= r) S[i].x.insert(j);
        else {
            put(2*i, l, (l+r)/2, u, v, j);
            put(2*i+1, (l+r)/2, r, u, v, j);
        }
    }

    void gen(int i, const vector<ll>&V) {
        vector<ll> W = V;
        for (int k: S[i].x) {
            for (int j = K-E[k].y; j >= 0; --j) {
                W[j+E[k].y] = max(W[j+E[k].y], W[j] + E[k].x);
            }
        }
        if (i < TT) {
            gen(2 * i, W);
            gen(2 * i + 1, W);
        } else {
            int P = 1e7+19;
            int M = 1e9+7;
            FieldMod R = 1, A = 0;
            for (int m = 1; m <= K; ++m) {
                A += R*(W[m]%M);
                R *= P;
            }
            S[i].y = A;
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> K;
        E.resize(N); cin >> E;
        vector<pii> T(N, {0,-1});
        int Q; cin >> Q;

        int Time = 0;
        vector<int> Query;
        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            if (t == 1) {
                int v, w;
                cin >> v >> w;
                E.push_back({v,w});
                T.push_back({++Time,-1});
            } else if (t == 2) {
                int i; cin >> i; --i;
                T[i].y = ++Time;
            } else {
                Query.push_back(Time);
            }
        }

        ++Time;
        for (pii&t:T) if (t.y == -1) t.y = Time;

        TT = 1<<logceil(Time);
        S.resize(2*TT);
        for (int i = 0; i < T.size(); ++i) {
            put(1, 0, TT, T[i].x, T[i].y, i);
        }
        vector<ll> V(K+1, 0);
        gen(1, V);

        for (int q:Query) {
            cout << S[q+TT].y << '\n';
        }

    }
};
