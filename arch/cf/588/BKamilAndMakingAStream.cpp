#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/nsegtree.h"


template <typename F> F LGcdOp(F a, F b) { return gcd(a, b); }
template <typename F> void LApplyTag(F &a, F b, ui i) { if (b != -1) a = b; }

template<typename T> using LAssignGcdTree = LSegTree<T, T, LAssignOp<T>, LApplyTag<T>, LGcdOp<T>>;


class BKamilAndMakingAStream {
public:
    int N;
    vector<ll> X;
    vector<vector<int>> E;
    LAssignGcdTree<ll> T{2, 0LL, 0LL};
    FieldMod ans = 0;


    int dfs(int u, int p, int i) {
        T.put(i, X[u]);
        int zeros = 0;
        for (int v : E[u]) {
            if (v != p) {
                zeros += dfs(v, u, i+1);
            }
        }

//        cerr << u << ' ' << p << ' ' << i << endl;
//        for (int j = 0; j <= i; ++j) cerr << T.get(j) << ' ';
//        cerr << endl;
        
        if (X[u] != 0) {
            FieldMod cur = 0;
            int j = i;
            ll mine = T.get(j);
            while (true) {
                int z = T.longestSuffix(j, [&](ll x) { return x%mine == 0; });
//                cerr << "Add " << mine << ' ' << j << ' ' << z << endl;
                cur += FieldMod(mine%1000000007LL) * (j-z+1);
                if (z == 0) break;
                j = z-1;
                mine = gcd(mine, T.get(j));
            }

            ans += cur * (zeros+1);
            return 0;
        } else {
            return zeros + 1;
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        X.resize(N); cin >> X;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        T = LAssignGcdTree<ll>(N, 0LL, -1LL);
        dfs(0, -1, 0);
        cout << ans << endl;
    }
};
