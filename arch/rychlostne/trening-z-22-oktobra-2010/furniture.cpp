#include "../l/lib.h"
// #include "../l/mod.h"

class furniture {
public:
    void solve(istream& cin, ostream& cout) {
        vector<ui> Q;
        while (true) {
            int q;
            if (!(cin >> q)) break;
            Q.push_back(q);
        }
        ui N = Q.size()/2;
        vector<ui> S(N), P(N);
        for (ui i = 0; i < N; ++i) {
            S[i] = Q[i];
            P[i] = Q[N+i];
        }

        ui smallest = *min_element(S.begin(),S.end());
        ui ans = 0;
        for (ui i = 0; i < N; ++i) {
            if (P[i] == i || P[i] == N) continue;
            ui sum = S[i], count = 1, lightest = S[i], j = P[i];
            P[i] = N;
            while (P[j] != N) {
                count++;
                lightest = min(lightest, S[j]);
                sum += S[j];
                ui k = P[j];
                P[j] = N;
                j = k;
            }

            ans += sum + min((count-2)*lightest, lightest+(count+1)*smallest);
        }

        cout << ans << endl;
    }
};
