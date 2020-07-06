#include "../l/lib.h"
#include "../l/mod.h"

class EMrAokiIncubator {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> U(N); cin >> U;
        sort(U.begin(), U.end());
        vector<int> LO(N), HI(N);

        vector<pii> Speed(N);
        for (int i = 0; i < N; ++i) Speed[i] = {U[i].y, i};
        sort(Speed.begin(),Speed.end());

        vector<int> IndexOfSpeed(N);
        for (int i = 0; i < N; ++i) IndexOfSpeed[Speed[i].y] = i;

        pii mx = {0, -1};
        for (int i = 0; i < N; ++i) {
            mx = max(mx, {U[i].y, IndexOfSpeed[i]});
            HI[i] = mx.y;
        }

        pii mn = {1e9 + 7, -1};
        for (int i = N-1; i >= 0; --i) {
            mn = min(mn, {U[i].y, IndexOfSpeed[i]});
            LO[i] = mn.y;
        }


        vector<vector<int>> Right(N);
        for (int i = 0; i < N; ++i) Right[LO[i]].push_back(HI[i]);

        vector<FieldMod> S(N+1, 0);
        S[0] = 1;
        FieldMod tot = 1;
        for (int i = 0; i < N; ++i) {
            for (int r: Right[i]) {
                S[r+1] += tot;
                tot *= 2;
            }
            tot -= S[i];
        }
        cout << S[N] << endl;
    }
};
