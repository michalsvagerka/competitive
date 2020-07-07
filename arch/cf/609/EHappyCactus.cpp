#include "../../../l/lib.h"
#include "../../../l/bridges.h"
#include "../../../l/graph.h"

class EHappyCactus {
public:
    /** Find cycles in cactus */
    vector<vector<int>> cycles(const vector<vector<int>> &E) {
        int N = E.size();
        vector<int> Processed(N, 0);
        vector<bool> Active(N, false);
        vector<vector<int>> Ans;
        for (int i = 0; i < N; ++i) {
            if (Processed[i] == E[i].size()) continue;
            vector<int> Stack{i};
            Active[i] = true;
            while (!Stack.empty()) {
                int u = Stack.back();
                if (Processed[u] == E[u].size()) {
                    Active[u] = false;
                    Stack.pop_back();
                } else {
                    int v = E[u][Processed[u]];
                    Processed[u]++;
                    if (Active[v]) {
                        if (Stack[Stack.size()-2] == v) continue;

                        Ans.push_back({v});
                        while (Stack.back() != v) {
                            Ans.back().push_back(Stack.back());
                            Active[Stack.back()] = false;
                            Stack.pop_back();
                        }
                    } else {
                        Stack.push_back(v);
                        Active[v] = true;
                    }
                }
            }
        }
        return Ans;
    }

    pii ed(int a, int b) { return {min(a,b), max(a,b)}; }
    
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> E(M); cin >> E;
        vector<vector<int>> F(N);
        for (pii &e:E) {
            e.x--;
            e.y--;
            if (e.x > e.y) swap(e.x, e.y);
            F[e.x].push_back(e.y);
            F[e.y].push_back(e.x);
        }

        auto Cyc = cycles(F);

        map<pii, int> ID;
        for (int i = 0; i < M; ++i) ID[E[i]] = i;

        vector<bool> Visited(N, false);
        vector<int> OppositeEdge(M, -1);
        for (auto&cyc: Cyc) {
            int W = cyc.size();
            pii lo = {ID[ed(cyc[0],cyc[W-1])], W-1};
            for (int i = 0; i < W-1; ++i) {
                lo = min(lo, {ID[ed(cyc[i],cyc[i+1])], i});
            }

            auto search = [&](int u, int diff, int edgeId) {
                while (true) {
                    int v = u+diff;
                    v = v==W?0:v;
                    v = v==-1?W-1:v;
                    int a = cyc[u], b = cyc[v];
                    if (ID[ed(a,b)] > edgeId) {
                        edgeId = ID[ed(a,b)];
                        u = v;
                    } else return edgeId;
                }
            };
            auto first = search(lo.y, -1, lo.x);
            auto second = search((lo.y+1)%W, 1, lo.x);

            if (first == second) OppositeEdge[lo.x] = first;
        }

        vector<int> H(N, 1), Sum(M, 0);
        for (int i = M-1; i >= 0; --i) {
            int a = E[i].x, b = E[i].y;
            int q = H[a] + H[b];
            if (OppositeEdge[i] != -1) q -= Sum[OppositeEdge[i]];
            H[a] = H[b] = Sum[i] = q;
        }

        for (int &h: H) --h;
        cout << H;
    }
};
