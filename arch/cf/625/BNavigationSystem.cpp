#include "../l/lib.h"

class BNavigationSystem {
public:
    int N, M, K;
    vector<int> P;
    vector<vector<int>> E, ER;

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        E.resize(N); ER.resize(N);
        for (int i = 0; i < M; ++i) {
            int u,v;cin>>u>>v;--u;--v;
            E[u].push_back(v);
            ER[v].push_back(u);
        }
        cin >> K;
        P.resize(K); cin >> P;
        for (int&p:P) --p;

        vector<int> D(N, -1), Q;
        int T = P.back();
        Q.push_back(T);
        D[T] = 0;
        for (int q = 0; q < Q.size(); ++q) {
            int a = Q[q];
            for (int b: ER[a]) {
                if (D[b] == -1) {
                    D[b] = D[a] + 1;
                    Q.push_back(b);
                }
            }
        }

        int lo = 0, hi = 0;
        for (int i = 0; i < K-1; ++i) {
            int a = P[i], c = P[i+1];
            int cnt = 0;
            for (int b : E[a]) cnt += D[b]+1 == D[a];
            lo += (D[c]+1 != D[a]);
            hi += (D[c]+1 != D[a]) || cnt >= 2;
        }
        cout << lo << ' ' << hi << endl;
    }
};
