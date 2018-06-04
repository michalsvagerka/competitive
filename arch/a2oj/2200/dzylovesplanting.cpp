#include "../../../l/lib.h"
#include "../../../l/util.h"

class dzylovesplanting {
public:

    void solve(istream& cin, ostream& cout) {

        int N;
        vector<int> X;
        vector<vector<pii>> E;

        cin >> N;
        if (N == 1) {
            cout << "0\n";
            return;
        }

        X.resize(N);
        E.resize(10001);
        for (int i = 0; i < N - 1; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            E[c].push_back({u-1,v-1});
        }

        cin >> X;
        int T = 0;
        UnionFind U(N);
        vector<int> S(N, 1);
        for (int i = 0; i < N; ++i) T += X[i];
        for (int c = 0; c <= 10000; ++c) {

//            for (int i = 0; i < N; ++i) {
//                if (U.find(i) == i && T - X[i] < S[i]) ok = false;
//            }


            for (pii e:E[c]) {
                int a = U.find(e.x);
                int b = U.find(e.y);
                U.unite(a,b);
                S[a] = S[b] = S[a] + S[b];
                X[a] = X[b] = X[a] + X[b];
                if (T - X[a] < S[a]) {
                    cout << c << endl;
                    return;
                }
            }
//
//            if (!E[c].empty()) {
//                cout << c << endl;
//                for (int i = 0; i < N; ++i) {
//                    if (U.find(i) == i) {
//                        cout << i << ' ' << S[i] << ' ' << T-X[i] << endl;
//                    }
//                }
//            }
        }

    }
};
