#include "../../../l/lib.h"
// #include "../l/mod.h"

class mashmokhandreverseoperation {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(1<<N); cin >> A;
        if (N == 0) {
            int M; cin >> M;
            while (M--) {
                cout << "0\n";
            }
            return;
        }

        vector<ll> Cor(N,0), Same(N,0), Inv(N,0);
        for (int i = 0; i < N; ++i) {
            vector<pii> F(2<<i);
            for (int j = 0; j < (1<<N); j+=(2<<i)) {
                for (int k = 0; k < (2<<i); ++k) {
                    F[k] = {A[j+k], k>=(1<<i)};
                }
                sort(F.begin(),F.end());
                int prev = -1, cnt = 0, lo = 0;
                for (pii &f: F) {
                    if (f.y == 0) {
                        if (prev != f.x) {
                            prev = f.x;
                            lo += cnt;
                            cnt = 1;
                        } else {
                            cnt++;
                        }
                    } else if (prev != f.x) {
                        prev = f.x;
                        lo += cnt;
                        cnt = 0;

                        Cor[i] += lo;
                    } else {
                        Cor[i] += lo;
                        Same[i] += cnt;
                    }
                }
            }
            Inv[i] = (1LL<<(N+i-1))-Same[i]-Cor[i];
        }

        int M; cin >> M;
        for (int q = 0; q < M; ++q) {
            int x; cin >> x;
            ll ans = 0;
            for (int i = 0; i < x; ++i) swap(Cor[i],Inv[i]);
            for (int i = 0; i < N; ++i) ans += Inv[i];
            cout << ans << '\n';
        }
    }
};
