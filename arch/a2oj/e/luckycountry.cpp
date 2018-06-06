#include "../../../l/lib.h"
 #include "../../../l/util.h"

constexpr int INF = (int)1e9;

class luckycountry {
public:
    vector<int> Lucky;

    void lucky(int x) {
        if (x > 1e5) return;
        if (x != 0) Lucky.push_back(x);
        lucky(10*x+4);
        lucky(10*x+7);
    }

    void solve(istream& cin, ostream& cout) {
        lucky(0);
        sort(Lucky.begin(),Lucky.end());

        int N,M;
        cin >> N >> M;
        UnionFind UF(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            UF.unite(u-1,v-1);
        }

        vector<int> S;
        for (int i = 0; i < N; ++i) if (UF.P[i] < 0) S.push_back(-UF.P[i]);
        sort(S.begin(),S.end());
        for (int s:S) {
            if (count(Lucky.begin(),Lucky.end(),s) > 0) {
                cout << 0 << endl;
                return;
            }
        }

        for (int i = 0; i < S.size(); ++i) {
            for (int lucky: Lucky) {
                if (lucky != 2*S[i] && binary_search(S.begin(),S.end(),lucky-S[i])) {
                    cout << 1 << endl;
                    return;
                } else if (lucky == 2*S[i] && i < S.size()-1 && S[i+1] == S[i]) {
                    cout << 1 << endl;
                    return;
                }
            }
        }

        int Q = 100;
        vector<int> T(Q+1, 0);
        for (int s:S) if (s <= Q) T[s]++;
        vector<pii> W;
        for (int i = 1; i <= Q; ++i) if (T[i]) W.push_back({T[i]*i,i});
        sort(W.begin(),W.end());

        vector<int> A(N+1, INF); A[0] = 0;
        int tot = 0;
        for (pii w:W) {
            for (int i = tot; i >= 0; --i) {
                if (A[i]!=INF) {
                    for (int j = 1, k = w.y; k <= w.x; j++, k+=w.y) A[i+k] = min(A[i+k], A[i]+j);
                }
            }
            tot += w.x;
        }

        vector<int> B(N+1, INF); B[0] = 0;
        tot = 0;
        for (int s:S) {
            if (s <= Q) continue;
            for (int i = tot; i >= 0; --i) {
                if (B[i]!=INF) B[i+s] = min(B[i+s], B[i]+1);
            }
            tot += s;
        }

        int ans = INF;
        for (int i = 0; i <= N; ++i) {
            for (int lucky: Lucky) {
                if (lucky <= N && lucky >= i && lucky-i >= 0) {
                    ans = min(ans, A[i]+B[lucky-i]);
                }
            }
        }

        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans-1 << endl;
        }


    }
};
