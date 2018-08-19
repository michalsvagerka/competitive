#include "../l/lib.h"
// #include "../l/mod.h"

constexpr ll inf = 3e18 + 1e17;

class Gift {
public:

    vector<ll> solveClique(const vector<ll> &T) {
        int N = T.size();
        if (N == 0) return {0LL};
        vector<ll> D(N, inf);
        D[0] = 0;
        vector<ll> P(N+1, 0);
        for (int i = 0; i < N; ++i) P[i+1] = P[i] + T[i];
        for (int j = 2; j <= N-2; j += 2) {
            D[j] = 0;
            for (int i = 0; i < j/2; ++i) {
                D[j] += T[1+i] * T[j-i];
            }
        }

        vector<ll> Ans(N+1, inf);
        if (N >= 2) Ans[1] = T[0] * T[1];
        Ans[0] = 0;
        ll best = inf;
        for (int j = 2; j <= N; ++j) {
            if (j%2==0) { best = min(best, D[j-2] - T[0] * P[j-1]); }
            Ans[j] = best + T[0] * P[j];
        }
        return Ans;
    }



void solve(istream& cin, ostream& cout) {

    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int N; cin >> N;
        vector<ll> L(N); cin >> L;
        vector<ll> Pos, Neg;
        for (ll l : L) if (l < 0) Neg.push_back(-l); else Pos.push_back(l);
        sort(Neg.begin(),Neg.end());
        sort(Pos.begin(),Pos.end());
        vector<ll> CNeg = solveClique(Neg);

        int A = Pos.size();
        int B = Neg.size();
        ll ans = inf;
        if (A==0) {
            ans = CNeg.back();
        } else if (B==0) {
            vector<ll> CPos = solveClique(Pos);
            ans = CPos.back();
        } else if (B==1) {
            ans = 0;
            for (ll pos:Pos) ans += pos;
            ans *= -Neg[0];
        } else {

            vector<ll> P(A+1, 0);
            for (int i = 0; i < A; ++i) P[i+1] = P[i] + Pos[i];

            for (int posConn = max(1, A-B+1); posConn <= A; ++posConn) {
                int negClique = B-1-(A-posConn);
                ll cur = - Neg[B-1] * (P[A] - P[A-posConn]) + CNeg[negClique];
                for (int i = 0; i + posConn < A; ++i) {
                    cur -= Pos[i] * Neg[negClique + i];
                }
                ans = min(cur, ans);
            }
        }

        cout << "Case #" << t+1 << ": " << ans << '\n';
    }

}
};
