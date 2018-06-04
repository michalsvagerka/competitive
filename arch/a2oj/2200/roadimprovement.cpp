#include "../../../l/lib.h"
#include "../../../l/mod.h"

class roadimprovement {
public:
    int N;
    vector<vector<int>> E;
    vector<int> S;
    vector<FieldMod> One;
    vector<FieldMod> Ans;

    int dfs(int u) {
        int s = 1;
        for (int v:E[u]) s += dfs(v);
        return S[u] = s;
    }

    void dfs2(int u) {
        One[u] = 1;
        for (int v:E[u]) {
            dfs2(v);
            One[u] *= One[v] + 2;
        }
        One[u]--;
    }

    void dfs3(int u, FieldMod oneFromTop) {
        if (u != 0) oneFromTop += 2;

        int M = E[u].size();
        vector<FieldMod> Child;
        for (int v:E[u]) {
            Child.push_back(One[v] + 2);
        }
        vector<FieldMod> Pref(M + 1, 1), Suf = Pref;
        for (int i = 0; i < M; ++i) {
            Pref[i+1] = Pref[i] * Child[i];
            Suf[M-i-1] = Suf[M-i] * Child[M-i-1];
        }


        for (int i = 0; i < Child.size(); ++i) {
            dfs3(E[u][i], oneFromTop * Pref[i] * Suf[i+1] - 1);
        }

        Ans[u] = (One[u]+1)*oneFromTop;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        S.resize(N);
        One.resize(N);
        Ans.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int p; cin >> p;
            E[p-1].push_back(i+1);
        }
        dfs(0);
        dfs2(0);
        dfs3(0, 1);
        cout << Ans;
    }
};
