#include "../l/lib.h"
#include "../l/bridges.h"
#include "../l/util.h"

class jednosmerky {
public:
    int N, M, K, TT;
    vector<vector<int>> E, Comp;
    vector<pii> F;
    vector<int> V, CI, T;
    vector<vector<int>> RouteA, RouteB;
    vector<pii> Answer;
    vector<vector<pair<int,pii>>> BrE;
    set<pii> Brset;

    bool dfs(int u, int p, set<int>&A, set<int>&B) {
        V[u] = true;
        for (auto v: BrE[u]) {
            if (v.x != p) {
                set<int> C, D;
                if (!dfs(v.x, u, C, D)) {
                    return false;
                }

                if (C.empty()) {
                    Answer.push_back({v.y.x,v.y.y});
                } else {
                    Answer.push_back({v.y.y,v.y.x});
                }

                if (A.size() + B.size() < C.size() + D.size()) {
                    swap(A, C);
                    swap(B, D);
                }

                for (int c: C) {
                    if (B.count(c)) {
                        B.erase(c);
                    } else {
                        A.insert(c);
                    }
                }

                for (int d: D) {
                    if (A.count(d)) {
                        A.erase(d);
                    } else {
                        B.insert(d);
                    }
                }
            }
        }

        for (int a: RouteA[u]) {
            if (B.count(a)) {
                B.erase(a);
            } else {
                A.insert(a);
            }
        }

        for (int b: RouteB[u]) {
            if (A.count(b)) {
                A.erase(b);
            } else {
                B.insert(b);
            }
        }

//        cerr << u << endl;
//        cerr << "A: ";
//        for (int a: A) cerr << a << ' ';
//        cerr << endl;
//        cerr << "B: ";
//        for (int b: B) cerr << b << ' ';
//        cerr << endl;

        return A.empty() || B.empty();
//        if (A.empty()) {
//            if (p != -1) Answer.push_back({p,u});
//            return true;
//        } else if (B.empty()) {
//            if (p != -1) Answer.push_back({u,p});
//            return true;
//        } else {
//            return false;
//        }
    }

    void dfs2(int u) {
        if (T[u] != -1) return;
        T[u] = TT++;

        for (int v : E[u]) {
            if (Brset.count({u,v})+Brset.count({v,u})>0) continue;
            if (T[v] == -1) {
                dfs2(v);
                Answer.push_back({u,v});
            } else if (T[v] > T[u]) {
                Answer.push_back({v,u});
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }
        cin >> K;
        F.resize(K);
        cin >> F;
        for (pii&f: F) { --f.x; --f.y; }

        Graph G(E);
        vector<pii> Bridges;
        G.bridges(Bridges);
        Brset = set<pii>(Bridges.begin(),Bridges.end());
        UnionFind UF(N);
        for (int i = 0; i < N; ++i) {
            for (int j: E[i]) {
                if (i<j && Brset.count({i,j})+Brset.count({j,i}) == 0) {
                    UF.unite(i,j);
                }
            }
        }

        CI.resize(N);

        Comp.resize(N);
        for (int i = 0; i < N; ++i) {
            CI[i] = UF.find(i);
            Comp[UF.find(i)].push_back(i);
        }

        BrE.resize(N);
        for (pii br: Bridges) {
            int u = CI[br.x];
            int v = CI[br.y];
            BrE[u].push_back({v, {br.x,br.y}});
            BrE[v].push_back({u, {br.y,br.x}});
        }

        RouteA.resize(N);
        RouteB.resize(N);
        for (int i = 0; i < K; ++i) {
            RouteA[CI[F[i].x]].push_back(i);
            RouteB[CI[F[i].y]].push_back(i);
        }

        V.assign(N, false);
        for (int i = 0; i < N; ++i) {
            if (!V[i]) {
                set<int> A,B;
                if (!dfs(i, -1, A, B)) {
                    cout << "No\n";
                    return;
                }
            }
        }

        T.assign(N, -1);
        TT = 0;
        for (int i = 0; i < N; ++i) dfs2(i);

        cout << "Yes\n";
        for (pii ans: Answer) {
            cout << ans.x+1 << ' ' << ans.y+1 << '\n';
        }

    }
};
