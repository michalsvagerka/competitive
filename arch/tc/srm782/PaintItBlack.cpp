#include "../l/lib.h"

class PaintItBlack {
public:
    void bipartite(int u, bool p, int par, const vector<vector<int>> &E, vector<bool>& V, vector<bool>& P, vector<int> &Par, pii& fail, bool&isBip) {
        if (V[u]) {
            if (P[u] == p) {}
            else {
                fail = {u,par};
                isBip = false;
            }
            return;
        }

        V[u] = true;
        P[u] = p;
        Par[u] = par;

        for (int v: E[u]) {
            bipartite(v, !p, u, E, V, P, Par, fail, isBip);
        }
    }

    void dfs(int u, int p, const vector<vector<int>> &E, vector<bool>&Parity, vector<int> &Path, bool first) {
        if (!first) {
            Path.push_back(u);
            Parity[u] = !Parity[u];
        }

        for (int v: E[u]) {
            dfs(v, u, E, Parity, Path, false);
            Path.push_back(u);
            Parity[u] = !Parity[u];
        }

        if (!Parity[u] && p != -1) {
            Path.push_back(p);
            Path.push_back(u);

            Parity[p] = !Parity[p];
            Parity[u] = !Parity[u];
        }
    }

    vector<int> bruteForce(int N) {
        vector2<int> A(1<<N, N, -1);
        vector<pii> Q{pii{1, 0}};
        for (auto q = 0; q < Q.size(); ++q) {
            pii e = Q[q];
            if (e.x == 0 && e.y == 0) {
                int x = e.x, y = e.y;
                vector<int> ans;
                while (x != 1 || y != 0) {
                    ans.push_back(y);
                    int z = A[x][y];
                    x = x^(1<<y);
                    y = z;
                }
                reverse(ans.begin(),ans.end());
                return ans;
            }
            int a = e.y-1, b = e.y+1;
            if (a == -1) a = N-1;
            if (b == N) b = 0;
            if (A[e.x^(1<<a)][a] == -1) {
                A[e.x^(1<<a)][a] = e.y;
                Q.push_back({e.x^(1<<a),a});
            }

            if (A[e.x^(1<<b)][b] == -1) {
                A[e.x^(1<<b)][b] = e.y;
                Q.push_back({e.x^(1<<b),b});
            }
        }
        return {};
    }

    vector <int> findWalk(int n, int u, vector <int> a, vector <int> b) {
        vector<vector<int>> E(n);
        int M = a.size();
        for (int i = 0; i < M; ++i) {
            E[a[i]].push_back(b[i]);
            E[b[i]].push_back(a[i]);
        }

        vector<bool> V(n, false), P(n, false);
        vector<int> Par(n, -1);
        pii fail = {0,0};
        bool bip = true;
        bipartite(u, false, -1, E, V, P, Par, fail, bip);
        if (bip && n%2 == 1) return {};
        vector<vector<int>> F(n);
        for (int i = 0; i < n; ++i) {
            if (Par[i] != -1) {
                F[Par[i]].push_back(i);
            }
        }

        vector<bool> Parity(n, false);
        vector<int> Path{u};
        dfs(u, -1, F, Parity, Path, true);
        if (Parity[u] == false) {
            vector<int> A{fail.x}, B{fail.y};
            while (A.back() != u) {
                int v = Par[A.back()];
                A.push_back(v);
            }
            while (B.back() != u) {
                int v = Par[B.back()];
                B.push_back(v);
            }
            reverse(A.begin(),A.end());
            reverse(B.begin(),B.end());
            int j = 0;
            while (j < A.size() && j < B.size() && A[j] == B[j]) ++j;
            for (int i = 1; i <= j-1; ++i) {
                Path.push_back(A[i]);
            }

            vector<int> C;
            for (int k = j-1; k < A.size(); ++k) C.push_back(A[k]);
            for (int k = int(B.size())-1; k >= j; --k) C.push_back(B[k]);
            int l = C.size();
            for (int k = 1; k <= l-2; k += 2) {
                Path.push_back(C[k]);
                Path.push_back(C[k+1]);
                Path.push_back(C[k]);
                Path.push_back(C[k+1]);
            }
            Path.push_back(C[0]);

            for (int i = j-2; i >= 0; --i) Path.push_back(A[i]);
        }

//        vector<int> C(n, 0);
//        for (int p:Path) {
//            C[p]++;
//        }
//        for (int i = 0; i < n; ++i) {
//            if (C[i]%2==0) {
//                cerr << "Fail " << i << endl;
//            }
//        }
        return Path;
    }
    void solve(istream& cin, ostream& cout) {
        cout << findWalk(2,0,{0},{1}) << endl;
        cout << findWalk(3,0,{0, 1},{1, 2}) << endl;
        cout << findWalk(3,0,{0, 1, 0},{1, 2, 2}) << endl;
        cout << findWalk(9,0,{0, 1, 2, 3, 4, 5, 6, 7, 8},{1, 2, 3, 4, 5, 6, 7, 8, 0}) << endl;
        cout << findWalk(13,10,{0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 10, 11},{1, 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 11, 12}) << endl;
        cout << findWalk(4,2,{0, 1, 2, 3},{1, 2, 3, 0}) << endl;
    }
};
