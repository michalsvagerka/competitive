#include "../l/lib.h"
#include "../l/primes.h"

constexpr int MX = 5000;

class DChaoticV {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> K(N); cin >> K;
        sort(K.begin(),K.end());
        vector<int> C(MX+1, 0);
        for (int k: K) C[k]++;

        vector<int> P = Sieve{MX}.primes();
        int M = P.size();

        vector2<int> D(MX+1, M, 0);
        for (int i = 0; i < M; ++i) {
            int p = P[i];
            for (int p = P[i]; p <= MX; p *= P[i]) {
                for (int j = 0; j <= MX; ++j) {
                    D[j][i] += j / p;
                }
            }
        }
        for (int i = 0; i <= MX; ++i) reverse(D[i].begin(),D[i].end());

        vector2<ll> Pref(MX+1, M+1, 0);
        for (int i = 0; i <= MX; ++i) {
            for (int j = 0; j < M; ++j) {
                Pref[i][j+1] = Pref[i][j] + D[i][j];
            }
        }

        vector<int> CountPref(MX+2, 0);
        ll tot = 0;
        for (int i = 0; i <= MX; ++i) {
            CountPref[i+1] = CountPref[i] + C[i];
            tot += C[i] * Pref[i].back();
        }

        int use = K[N/2];
        vector<pair<ll, int>> W;
        ll base = 0;
        for (int i = 0; i <= MX; ++i) {
            if (C[i] == 0) continue;

            int x = 0;
            ll len = 0;
            while (x < M && D[i][x] == D[use][x]) {
                len += D[i][x];
                x++;
            }
            if (x < M) {
                len += min(D[i][x], D[use][x]);
            }
            W.push_back({len, C[i]});
            base += (Pref[i][M] - len) * C[i];
        }
        sort(W.begin(),W.end());

        ll ans = 1e18;
        for (auto w: W) {
            ll cur = 0;
            for (auto ww: W) {
                cur += abs(ww.x - w.x) * ww.y;
            }
            ans = min(ans, base + cur);
        }
        cout << ans << '\n';
    }
};
