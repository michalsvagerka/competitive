#include "../l/lib.h"
// #include "../l/mod.h"

class cielandgondolas {
public:

    vector<vector<int>> P;

    inline int get(int i, int j) {
        return P[j][j] + P[i][i] - P[j][i] - P[i][j];
    }

    void dnc(const vector<int>&src, vector<int>&tar, int left, int right, int lo, int hi) {
        if (left >= right) return;

        int center = (left+right)/2;
        pii best = {src[lo] + get(lo,center), lo};
        for (int i = lo+1; i < hi; ++i) best = min(best, {src[i] + get(i,center), i});
        tar[center] = best.x;
        dnc(src, tar, left, center, lo, best.y+1);
        dnc(src, tar, center+1, right, best.y, hi);
    }


    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        P = vector2<int>(N+1, N+1, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                char c; cin >> c;
                P[i+1][j+1] = c-'0' + P[i+1][j] + P[i][j+1] - P[i][j];
            }
        }

        vector<int> D(N+1, 1e9);
        vector<pair<pii,pii>> Q(N+1);
        Q[0] = {{0,N+1},{0,N+1}};

        D[0] = 0;
        for (int k = 0; k < K; ++k) {
            vector<int> E(N+1, 0);
            int j = 1;
            for (int i = 0; i <= N; ++i) {
                auto q = Q[i];

                int center = (q.x.x+q.x.y)/2;
                pii best = {D[q.y.x] + get(q.y.x,center), q.y.x};
                for (int i = q.y.x+1; i < q.y.y; ++i) best = min(best, {D[i] + get(i,center), i});
                E[center] = best.x;
                if (q.x.x < center) Q[j++] = {{q.x.x, center}, {q.y.x, best.y+1}};
                if (center+1 < q.x.y) Q[j++] = {{center+1, q.x.y}, {best.y, q.y.y}};
            }
            swap(E,D);
        }

        cout << D[N]/2;
    }
};
