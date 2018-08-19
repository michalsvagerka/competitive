#include "../l/lib.h"
// #include "../l/mod.h"

class Parcels {
public:

    struct Parc {
        int i, o, w, s, v;
    };

void solve(istream& cin, ostream& cout) {
    int N, S; cin >> N >> S;
    vector<Parc> P(N+1);
    for (int i = 0; i < N; ++i) {
        cin >> P[i].i >> P[i].o >> P[i].w >> P[i].s >> P[i].v;
    }
    P[N].i = 0;
    P[N].o = 2*N;
    P[N].w = 0;
    P[N].s = S;
    P[N].v = 0;

    sort(P.begin(),P.end(),[](const Parc&a, const Parc&b) { return a.o < b.o || (a.o == b.o && a.i > b.i); });

    vector2<int> V(N+1, S+1, 0);
    vector<int> Z(2*N+1, 0), O(N), I(N), C(N), Q;

    for (int i = 0; i <= N; ++i) {

        Q.clear();
        for (int j = 0; j < i; ++j) {
            if (P[j].i >= P[i].i && P[j].o <= P[i].o) {
                Q.push_back(j);
            }
        }
        sort(Q.begin(),Q.end(),[&](int a, int b) { return P[a].i < P[b].i; });

        for (int i = 0; i < Q.size(); ++i) {
            O[i] = P[Q[i]].o;
            I[i] = P[Q[i]].i;
            C[i] = P[Q[i]].s + P[Q[i]].w;
        }

        fill(Z.begin() + P[i].i, Z.begin() + P[i].o + 1, 0);
        for (int s = 0; s <= S - P[i].w; ++s) {
            int k = 0;
            for (int t = P[i].i; t < P[i].o; ++t) {
                while (k < Q.size() && I[k] == t) {
                    Z[O[k]] = max(Z[O[k]], Z[t] + V[Q[k]][min(s, C[k])]);
                    ++k;
                }
                Z[t+1] = max(Z[t+1], Z[t]);
            }

            V[i][s + P[i].w] = Z[P[i].o] + P[i].v;
        }
    }

    cout << V[N][S] << endl;
}
};
