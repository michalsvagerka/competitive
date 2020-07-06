#include "../l/lib.h"
#include "../l/mod.h"

class covidcampus {
public:
    void solve(istream& cin, ostream& cout) {
        int D, N; cin >> D >> N;
        D = min(D, 500);

        vector<FieldMod> Asc(N+1, 0);
        vector<FieldMod> Desc(N+1, 0);
        Asc[0] = 1;
        Desc[0] = 1;
        FieldMod ans = 0;
        for (int i = 1; i <= D; ++i) {
            for (int j = N; j >= i; --j) Asc[j] = Asc[j-i];
            for (int j = i-1; j >= 0; --j) Asc[j] = 0;
            for (int j = 0; j + i <= N; ++j) Asc[j+i] += Asc[j];

            for (int j = 0; j <= N; ++j) ans += Asc[j] * Desc[N-j];

            for (int j = 0; j + i <= N; ++j) Desc[j+i] += Desc[j];
        }

        cout << ans << '\n';
    }
};
