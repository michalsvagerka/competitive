#include "../../../l/lib.h"
// #include "../l/mod.h"

// 0  4  8  12 16 20 24
// 7  11 15 19 23 27
// 14 18 22 26 30
// 21 25 29 33
// 28 32 36
// 35 39
// 42

constexpr int dig = 19;

class luckynumberrepresentation {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll N; cin >> N;

            vector2<pair<pii,int>> D(dig+1, 10, {{-1,-1},-1});
            vector<int> W(dig);
            D[0][0] = {{0,0},0};
            ll X = N;
            for (int i = 0; i < dig; ++i) { W[i] = X%10; X /= 10; }
            for (int i = 0; i < dig; ++i) {
                for (int j = 0; j < 10; ++j) {
                    if (D[i][j].y != -1) {
                        for (int k = 0; k <= 6 ; ++k) {
                            for (int l = 0; k+l <= 6; ++l) {
                                if ((j+4*k+7*l)%10 == W[i]) {
                                    D[i+1][(j+4*k+7*l)/10] = {{k,l},j};
                                }
                            }
                        }
                    }
                }
            }
            if (D[dig][0].y == -1) {
                cout << "-1\n";
            } else {
                vector<ll> V(6, 0);
                int j = 0;
                for (int i = dig; i > 0; --i) {
                    for (int z = 0; z < 6; ++z) V[z] *= 10;
                    for (int k = 0; k < D[i][j].x.x; ++k) V[k] += 4;
                    for (int l = D[i][j].x.x; l < D[i][j].x.x+D[i][j].x.y; ++l) V[l] += 7;
                    j = D[i][j].y;
                }
                cout << V;
            }
        }

    }
};
