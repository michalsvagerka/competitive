#include "../../../l/lib.h"
// #include "../l/mod.h"


class poloandtrees {
public:
    int N;
    vector<vector<int>> E;
    
    vector<int> S;

    int size(int u, int p) {
        int s = 1;
        for (int v:E[u]) if (v!=p) s += size(v,u);
        return S[u] = s;
    }

    ull solve(int u, int p) {
        ull tot1 = 0, tot11 = 0, tot111 = 0, tot1111 = 0;
        ull tot2 = 0, tot22 = 0, tot21 = 0, tot211 = 0;
        ull totFail = 0;

        ull ans = 0;
        ull tot = 0;
        for (int v:E[u]) {
            if (v!=p) {
                ull s = ull(S[v]);
                ull ss = ull(S[v]) * (S[v]-1)/2;
                tot211 += tot21 * s;
                tot211 += tot11 * ss;
                tot21 += tot1 * ss;
                tot21 += tot2 * s;
                tot1111 += tot111 * s;
                tot111 += tot11 * s;
                tot11 += tot1 * s;
                tot1 += s;
                tot22 += tot2 * ss;
                tot2 += ss;
                ans += solve(v,u);
            }
        }

        ull three = 0;
        three += 3*tot111; // 3 from dist children (select the free)
        three += 3*tot11; // 2 from dist children & 1 root (select the free)
        three += 2*tot2; // 2 from same child & 1 root (select the root match)
        three += 2*tot21; // 2 from same child & 1 from different (select the diff match)
        three *= N-S[u]; // select something from top
        three *= 2; // permute (a,b)  and (c,d)

        ull four = 0;
        four += 6*tot1111; // four different branches (+select a and b)
        four += 4*tot22; // two different branches (+select a and b)
        four += 4*tot211; // three different branches (+select a and b)
        four += 6*tot111; // three branches and root (+ select a and b)
        four += 4*tot21;  // two branches and root (+select a and b)

        return ans+three+four;
    }
//


    bool dfs(int u, int p, int w, vector<bool> &V) {
        V[u] = true;
        if (u==w) return true;

        for (int v:E[u]) {
            if (v != p) {
                if (dfs(v, u, w, V)) {
                    return true;
                }
            }

        }

        V[u] = false;
        return false;
    }
    
    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        S.resize(N);
        size(0, -1);

        ull ans = (ull(N)*ull(N-1)/2)*(ull(N-2)*ull(N-3)/2);
        ans -= solve(0, -1);
        cout << ans << '\n';

    }
};
