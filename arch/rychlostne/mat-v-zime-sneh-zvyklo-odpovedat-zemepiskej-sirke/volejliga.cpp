#include "../l/lib.h"
// #include "../l/mod.h"

class volejliga {
public:
    int N, W, Z;
    vector<pii> Pairs;
    vector<int> Pts;
    vector<vector<int>> D, Res, Res2;

    void gen(int i, int I) {
        if (i == I) Res.push_back(Pts);
        else {
            int a = Pairs[i].x, b = Pairs[i].y;
            if (D[a][b] != -1) {
                Pts[a] += D[a][b];
                Pts[b] += 1 - D[a][b];
                if (Pts[a] <= W && Pts[b] <= W) gen(i+1, I);
                Pts[a] -= D[a][b];
                Pts[b] -= 1 - D[a][b];
            } else {
                Pts[a]++;
                if (Pts[a] <= W) gen(i+1, I);
                Pts[a]--;
                Pts[b]++;
                if (Pts[b] <= W) gen(i+1, I);
                Pts[b]--;
            }
        }
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> Z;
        W = N/2;
        D = vector2<int>(N, N, -1);
        for (int i = 0; i < Z; ++i) {
            int a, b; cin >> a >> b;
            D[a][b] = 1;
            D[b][a] = 0;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                Pairs.emplace_back(i,j);
            }
        }

        Pts.assign(N, 0);

        gen(0, Pairs.size()/2);
        Res2 = Res;
        Res.clear();
        gen(Pairs.size()/2, Pairs.size());

        map<vector<int>, int> A, B;
        for (auto &r: Res) A[r]++;
        for (auto &r: Res2) B[r]++;
        ll ans = 0;
        for (auto &a: A) {
            vector<int> Z(N);
            for (int i = 0; i < N; ++i) Z[i] = W - a.x[i];
            ans += ll(a.y) * B[Z];
        } 
        cout << ans << '\n';
    }
};
