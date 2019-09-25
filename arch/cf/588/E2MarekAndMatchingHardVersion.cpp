#include "../l/lib.h"
#include "../l/mod.h"

constexpr int S = 128;
namespace std {
    template<std::size_t N> bool operator<(const std::bitset<N> &x, const std::bitset<N> &y) {
        for (int i = N - 1; i >= 0; i--) {
            if (x[i] ^ y[i]) return y[i];
        }
        return false;
    }
}

class E2MarekAndMatchingHardVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> P(N, N); cin >> P;
        map<bitset<S>, FieldMod> G;
        G[1] = 1;
        for (int i = 0; i < N; ++i) {
            map<vector<int>, FieldMod> H; 
            for (auto g: G) {
                vector<int> S;
                for (int m = 0; m < (1<<N); ++m)if (g.x[m]) S.push_back(m);
                H[S] = g.y;
            }
            G.clear();
            for (int j = 0; j < (1<<N); ++j) {
                FieldMod pst = 1;
                for (int k = 0; k < N; ++k) if (j&1<<k) pst *= P[i][k]; else pst *= 100 - P[i][k];
                for (auto h: H) {
                    bitset<S> ans;
                    for (int l = 0; l < N; ++l) {
                        if ((j&1<<l) == 0) continue;
                        for (int m: h.x) if ((m&1<<l) == 0) ans[m | 1<<l] = true;
                    }
                    if (ans.any()) G[ans] += h.y * pst;
                }
            }
        }

        FieldMod ans = 0;
        for (auto g: G) ans += g.y;
        for (int i = 0; i < N*N; ++i) ans /= 100;
        cout << ans << endl;
    }
};
