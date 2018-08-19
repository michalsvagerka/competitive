#include "../l/lib.h"
// #include "../l/mod.h"

class Finshakes {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, M, W; cin >> N >> M >> W;
        vector<int> H(N); cin >> H;
        vector<pii> R;
        for (int i = 0; i < M; ++i) {
            int p, j; cin >> p >> j;
            --p;
            int l = p, r = p;
            while (l != 0 && H[l] + j > W) --l;
            while (r != N-1 && H[r] + j > W) ++r;
            R.push_back({l,r+1});
        }

        vector2<int> D(N+1, N+1, 0);
        for (int l = 1; l <= N; ++l) {
            for (int b = 0; b + l <= N; ++b) {
                for (int c = b; c < b+l; ++c) {
                    int f = 0;
                    for (pii r:R) if (b <= r.x && r.x <= c && c < r.y && r.y <= b+l) ++f;
                    D[l][b] = max(D[l][b], D[c-b][b] + D[b+l-c-1][c+1] + f * (f-1)/2);
                }
            }
        }


        cout << "Case #" << t+1 << ": " << D[N][0] << '\n';
    }

}
};
