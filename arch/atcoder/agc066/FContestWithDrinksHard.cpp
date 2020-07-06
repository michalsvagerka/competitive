#include "../l/lib.h"
#include "../l/envelope.h"

class FContestWithDrinksHard {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> T(N); cin >> T;
        int M; cin >> M;
        vector<pii> P(M); cin >> P;

        vector2<ll> DP(2, N+1, 0);
        vector2<vector<ll>> Fragments(2, N);

        for (int t = 0; t < 2; ++t) {
            vector<ll> Pref(N + 1, 0);
            for (int i = 0; i < N; ++i) Pref[i + 1] = Pref[i] + T[i];
            Envelope::Upper<ll> Env;
            for (ll i = 0; i < N; ++i) {
                Env.insert_line(-2 * i, 2 * DP[t][i] + i * i - i + 2 * Pref[i], i);
                for (int j = i; j < N && (j&i) == i; ++j) {
                    // we do O(N log N) envelopes here, how can we improve?
                    // linear CHT doesn't help, because the amortization argument is gone
                    ll best = (j + 1) * (j + 2) - 2 * Pref[j+1] + Env[j+1];
                    Fragments[t][i].push_back(best / 2);
                }
                DP[t][i + 1] = max(DP[t][i], Fragments[t][i][0]);
            }
            reverse(T.begin(),T.end());
        }

        vector<ll> With(N, -1e12), Without(N);
        for (int i = 0; i < N; ++i) Without[i] = DP[0][i] + DP[1][N-1-i];

        // sum of length of fragments is O(N log N), so the following is O(N log N)
        for (int t = 0; t < 2; ++t) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < Fragments[t][i].size(); ++j) {
                    Fragments[t][i][j] += DP[1-t][N - i - j];
                }
                for (int j = int(Fragments[t][i].size())-1; j > 0; --j) {
                    Fragments[t][i][j-1] = max(Fragments[t][i][j-1], Fragments[t][i][j]);
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < Fragments[0][i].size(); ++j) {
                With[i] = max(With[i], Fragments[0][i][j]);
                With[i + j] = max(With[i + j], Fragments[0][i][j]);
            }
            for (int j = 0; j < Fragments[1][i].size(); ++j) {
                With[N-1-i] = max(With[N-1-i], Fragments[1][i][j]);
                With[N-1-i-j] = max(With[N-1-i-j], Fragments[1][i][j]);
            }
        }

        for (pii p: P) {
            p.x--;
            cout << max(Without[p.x], max(0LL, With[p.x] + T[p.x] - p.y)) << '\n';
        }
    }
};
