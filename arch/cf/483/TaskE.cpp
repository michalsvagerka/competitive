#include "../../../l/lib.h"
#include "../../../l/graph.h"

class TaskE {
public:

    map<pii, unordered_set<int>> Z;
    map<pii, unordered_set<int>> W;
    map<pii, int> S;

    Tree T;

    void precompute(int i, int p) {
        if (S[{i,p}] == 0) return;

        if (W.find({i,p}) != W.end()) return;

        W[{i,p}] = Z[{i,p}];
        for (int j : T.E[i]) {
            if (j > i) {
                precompute(j, p);
                for (int k : W[{j,p}]) {
                    W[{i,p}].insert(k);
                }
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N-1); cin >> P;
        int M; cin >> M;
        vector<pii> B(M); cin >> B;
        sort(B.begin(),B.end());
        B.resize(distance(B.begin(),unique(B.begin(),B.end())));

        int Q; cin >> Q;
        vector<pii> C(Q); cin >> C;

        vector<int> Ans(Q, -1);

        T = Tree(N);
        for (int i = 0; i < N-1; ++i) {
            T.addEdge(P[i]-1, i+1);
        }
        T.calcLA();


        vector2<pii> H(20, N);
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < N; ++j) {
                H[i][j] = {T.D[j],j};
            }
        }


        for (int i = 0; i < M; ++i) {
            pii &b = B[i];
            --b.x; --b.y;
            int l = T.lca(b.x,b.y);
            H[0][b.x] = min(H[0][b.x], {T.D[l], l});
            H[0][b.y] = min(H[0][b.y], {T.D[l], l});
            Z[{b.x, l}].insert(i);
            Z[{b.y, l}].insert(i);
            S[{b.x, l}]++;
            S[{b.y, l}]++;
        }

        for (auto it = S.rbegin(); it != S.rend(); ++it) {
            auto i = it->x.x;
            auto p = it->x.y;
            auto s = it->y;

            if (i != 0) S[{P[i-1]-1, p}] += s;
        }

        for (int i = 0; i < N-1; ++i) {
            H[0][P[i]-1] = min(H[0][P[i]-1], H[0][i+1]);
        }

        for (int i = 1; i < 20; ++i) {
            for (int j = 0; j < N; ++j) {
                H[i][j] = min(H[i][j], H[i-1][H[i-1][j].y]);
            }
        }

        for (int i = 0; i < Q; ++i) {
            pii &c = C[i];
            --c.x; --c.y;
            int l = T.lca(c.x, c.y);
            if (T.D[l] >= H[19][c.x].x && T.D[l] >= H[19][c.y].x) {
                Ans[i] = 0;
                int d = c.x;
                for (int j = 19; j >= 0; --j) {
                    if (H[j][d].x > T.D[l]) {
                        d = H[j][d].y;
                        Ans[i] += 1<<j;
                    }
                }

                int e = c.y;
                for (int j = 19; j >= 0; --j) {
                    if (H[j][e].x > T.D[l]) {
                        e = H[j][e].y;
                        Ans[i] += 1<<j;
                    }
                }

                Ans[i]++;
                if (e == l || d == l) continue;

                // add one if there is no direct route from (d,e)
                if (S[{e,l}] == 0 || S[{d,l}] == 0) { Ans[i]++; continue; }
                if (S[{e,l}] < S[{d,l}]) swap(e,d);
                precompute(e,l);
                precompute(d,l);

                bool found = false;
                for (int t : W[{d,l}]) {
                    if (W[{e,l}].find(t) != W[{e,l}].end()) {
                        found = true;
                        break;
                    }
                }
                if (!found) Ans[i]++;
            }
        }



        for (int ans: Ans) cout << ans << '\n';
    }
};
