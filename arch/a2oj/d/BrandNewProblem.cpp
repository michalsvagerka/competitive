#include "../l/lib.h"
// #include "../l/mod.h"

class BrandNewProblem {
public:
void solve(istream& cin, ostream& cout) {
    unordered_map<string, int> S;
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        string T; cin >> T;
        S[T] = i;
    }

    pii ans = {N*(N-1)/2+1, -1};
    vector2<int> D(1<<N, N*(N-1)/2+1);
    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        int K; cin >> K;
        vector<int> L;
        for (int j = 0; j < K; ++j) {
            string G; cin >> G;
            auto it = S.find(G);
            if (it != S.end()) L.push_back(it->y);
        }

        int R = L.size();
        vector2<int> I(R+1, N, R);
        for (int k = R-1; k >= 0; --k) {
            for (int j = 0; j < N; ++j) {
                I[k][j] = I[k+1][j];
                if (L[k] == j) I[k][j] = k;
            }
        }

        for (int l = 0; l < (1<<N); ++l) {
            for (int k = 0; k < ans.x; ++k) {
                D[l][k] = 1e9;
            }
        }

        minheap<pair<int,pii>> H;
        H.push({0,{0,0}});
        D[0][0] = 0;
        while (!H.empty()) {
            auto h = H.top(); H.pop();
            if (D[h.y.x][h.y.y] < h.x) continue;
            if (h.x == R) break;

            for (int j = 0; j < N; ++j) {
                if (h.y.x&(1<<j)) continue;
                int n = I[h.x][j];
                int m = h.y.x|(1<<j);
                int g = h.y.y + __builtin_popcount(h.y.x&~((1<<j)-1));
                if (g < ans.x && D[m][g] > n) {
                    D[m][g] = n;
                    H.push({n, {m, g}});
                }
            }
        }

        for (int k = 0; k < ans.x; ++k) {
            if (D.back()[k] < R) {
                ans = {k, i+1};
                break;
            }
        }

        if (ans.x == 0) break;
    }

    if (ans.x == N*(N-1)/2+1) {
        cout << "Brand new problem!\n";
    } else {
        cout << ans.y << "\n[:" << string(N*(N-1)/2-ans.x+1, '|') << ":]\n";
    }
}
};
