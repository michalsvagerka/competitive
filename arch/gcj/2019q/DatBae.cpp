#include "../l/lib.h"

class DatBae {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, B, F; cin >> N >> B >> F;
            int r = 1;
            while ((1<<r) < N) ++r;
            r = min(r, 4);
            
            vector<string> Ans(r);
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << ((j >> i) & 1);
                }
                cout << endl;
                cin >> Ans[i];
                if (Ans[i] == "-1") return;
            }

            vector<bool> U(N, false);
            vector<int> G;
            for (int i = 0; i < N - B; ++i) {
                int x = 0;
                for (int j = 0; j < r; ++j) {
                    x ^= (Ans[j][i] - '0') << j;
                }
                G.push_back(x);
            }
            for (int i = 1; i < N - B; ++i) {
                while (G[i] <= G[i-1]) G[i] += 16;
            }
            for (int g: G) U[g] = true;
            
            
            vector<int> Ret;
            for (int i = 0; i < N; ++i) {
                if (!U[i]) Ret.push_back(i);
            }
            cout << Ret;
            flush(cout);

            int rep;
            cin >> rep;
            if (rep == -1) return;
        }
    }
};
