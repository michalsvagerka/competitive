#include "../../../l/lib.h"

class FComputePower {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N); cin >> A >> B;

        map<int, vector<int>> Proc;
        for (int i = 0; i < N; ++i) {
            Proc[-A[i]].push_back(B[i]);
        }

        // sumB * free -> min sumA
        ll INF = 1e18;
        vector2<ll> D(5001, 51, INF);
        D[0][0] = 0;
        for (auto &p: Proc) {
            vector2<ll> E(5001, 51, INF);
            sort(p.y.begin(),p.y.end());
            reverse(p.y.begin(),p.y.end());
            vector<int> sumB(p.y.size()+1, 0);
            for (int i = 0; i < p.y.size(); ++i) sumB[i+1] = sumB[i] + p.y[i];

            for (int i = 0; i <= 5000; ++i) {
                for (int j = 0; j <= 50; ++j) {
                    if (D[i][j] != INF) {
                        for (int k = 0; k <= p.y.size(); ++k) {
                            int l = p.y.size() - k;
                            if (l > j) continue;
                            E[i+sumB[k]][j-l+k] = min(E[i+sumB[k]][j-l+k], D[i][j] + k*ll(-p.x));
                        }
                    }
                }
            }
            swap(D,E);
        }


        ll ans = INF;
        for (int i = 0; i <= 5000; ++i) {
            for (int j = 0; j <= 50; ++j) {
                if (D[i][j] != INF) {
                    ll t = (1000LL * D[i][j] + i-1) / i;
                    ans = min(ans, t);
                }
            }
        }
        cout << ans << '\n';
    }
};
