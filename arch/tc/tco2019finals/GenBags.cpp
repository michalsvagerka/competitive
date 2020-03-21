#include "../l/lib.h"
#include "../l/random.h"

class GenBags {
public:
    static ll grundy(const vector<ll>& V) {
        return V[3] + (V[0] + V[2] + 2*V[1] + 2*min(V[0],V[2]))/4;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        cout << T << endl;
        for (int t = 0; t < T; ++t) {

            int N, M; ll Max;
            cin >> N >> M >> Max;
            vector<vector<ll>> V(N);
            random_ll R{0, Max};
            vector<ll> G(N, 0);
            for (int i = 0; i < M; ++i) {
                V[i] = {R(rng), R(rng), R(rng), R(rng)};
                G[i] = grundy(V[i]);
            }

            random_ll RM(0, (1LL<<M)-1);
            for (int i = M; i < N; ++i) {
                int mask = RM(rng);
                for (int j = 0; j < M; ++j) {
                    if (mask&(1LL<<j)) G[i] ^= G[j];
                }

                V[i] = vector<ll>(4, 0LL);
                for (int j = 0; j < 3; ++j) {
                    V[i][j] = random_ll{0, bsh(0LL, Max, [&](ll x) { V[i][j] = x; return grundy(V[i]) <= G[i]; })}(rng);
                }
                V[i][3] = G[i] - grundy(V[i]);
                if (V[i][3] > Max) --i;
            }

            shuffle(V.begin(),V.end(),rng);
            
            if (1) {
                cout << N << endl;
                auto print = [&](int j) {
                    cout << "{";
                    for (int i = 0; i < N; ++i) cout << V[i][j] << ", "[i==N-1];
                    cout << "}\n";
                };
                for (int i = 0; i < 4; ++i) print(i);
            } else {
                cout << "System.out.println(bon.wonByAlice(" << N;
                auto print = [&](int j) {
                    cout << ", new long[]{";
                    for (int i = 0; i < N; ++i) cout << V[i][j] << 'L' << ", "[i==N-1];
                    cout << "}";
                };
                for (int i = 0; i < 4; ++i) print(i);
                cout << "));\n";
            }
        }
    }
};
