#include "../l/lib.h"
 #include "../l/mod.h"

class SerejaAndCinema {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;

    auto F = FieldMod::fact(N+5);
    auto I = FieldMod::invfact(N+5);

    vector<int> A(N); cin >> A;
    vector<pii> Z{{N,N}};
    for (int i = 0; i < N; ++i) {
        if (A[i]) {
            Z.push_back({A[i]-1, i});
        }
    }
    sort(Z.begin(),Z.end());

    FieldMod ans = 0;
    for (int w : {-1, 1}) {
        if (Z[0].x == 0 && w == 1) continue;

        int l = Z[0].y, r = l;
        if (w == -1) l -= Z[0].x; else r += Z[0].x;
        if (l < 0 || r > N) continue;

        FieldMod cur = Z[0].x >= 2 ? FieldMod{2}.pow(Z[0].x-1) : 1;

        for (int i = 1; i < Z.size(); ++i) {
            int dt = Z[i].x - Z[i-1].x;
            int j = Z[i].y;
            if (j >= l && j <= r) { cur = 0; break; }
            if (j < l-dt) { cur = 0; break; }
            if (j > r+dt) { cur = 0; break; }
            --dt;
            int d;
            if (j < l) {
                d = l - j - 1;
                l = j;
                r += dt - d;
                if (r > N) { cur = 0; break; }
            } else {
                d = j - r - 1;
                r = j;
                l -= dt - d;
                if (l < 0) { cur = 0; break; }
            }

            cur *= F[dt] * I[d] * I[dt-d];
        }

        ans += cur;
    }

    cout << ans << '\n';
}
};
