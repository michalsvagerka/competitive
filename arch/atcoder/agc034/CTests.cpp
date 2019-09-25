#include "../l/lib.h"

class CTests {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        ll X; cin >> X;
        vector<ll> B(N), L(N), U(N);
        for (int i = 0; i < N; ++i) {
            cin >> B[i] >> L[i] >> U[i];
        }

        ll tot = 0;
        vector<pair<ll, int>> Gain(N);
        vector<ll> S(N);
        for (int i = 0; i < N; ++i) {
            tot += -L[i] * B[i];
            S[i] = U[i] * X + B[i] * (L[i] - U[i]);
            Gain[i] = {S[i], i};
        }
        sort(Gain.begin(),Gain.end());
        reverse(Gain.begin(),Gain.end());
        vector<int> I(N);
        for (int i = 0; i < N; ++i) {
            I[Gain[i].y] = i;
        }

        vector<ll> Pref(N+1, 0);
        for (int i = 0; i < N; ++i) {
            Pref[i+1] = Pref[i] + Gain[i].x;
        }

        ll ans = ll(X) * N;
        for (int i = 0; i < N; ++i) {
            ll g = bsl(0LL, N, [&](int j) {
                return Pref[j] + tot >= 0;
            });

            for (ll f = max(0LL,g-1); f <= g; ++f) {
                ll y = Pref[f];
                ll mine = f * X;
                if (i < f) {
                    y -= Gain[i].x;
                    mine -= X;
                }

                ll cur = tot + y;


                int k = Gain[i].y;

                ll lo = bsl(0LL, X, [&](int x) { return x * L[k] + cur >= 0; });
                ll hi = bsl(0LL, X, [&](int x) { return x * U[k] + B[k] * (L[k] - U[k]) + cur >= 0; });
                if (lo != -1) {
                    ans = min(ans, mine + lo);
                }
                if (hi != -1) {
                    ans = min(ans, mine + hi);
                }
            }
        }
        cout << ans << endl;
    }
};
