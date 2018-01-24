#include "../l/lib.h"
#include "../l/mod.h"

class bobzahon {
public:
    vector<vector<pii>> T;
    vector<int> C;

    bool dfs(int u, int c) {
        if (C[u] == c) return true;
        if (C[u] == -c) return false;
        C[u] = c;
        for (pii&t:T[u]) {
            if (!dfs(t.x,t.y*c)) return false;
        }
        return true;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        if (A[0] == -1) A[0] = N;
        if (A[0] != N) { cout <<"0\n"; return; }
        for (int i = 1; i < N; ++i) { if (A[i] + i > N) { cout << "0\n"; return; } }
        T.resize(N);
        C=vector<int>(N,0);
        for (int i = 1; i < N; ++i) {
            if (A[i] != -1) {
                for (int j = 0; j < A[i]; ++j) {
                    T[j].emplace_back(i+j,1);
                    T[i+j].emplace_back(j,1);
                }
                if (i+A[i] < N) {
                    T[A[i]].emplace_back(i + A[i], -1);
                    T[i + A[i]].emplace_back(A[i], -1);
                }
            }
        }

        int ch = 0;
        for (int i = 0; i < N; ++i) {
            if (!C[i]) {
                ++ch;
                if (!dfs(i,1)) {
                    cout << "0\n";
                    return;
                }
            }
        }

        cout << FieldMod(2).pow(ch) << endl;
    }
};
