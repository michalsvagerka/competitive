#include "../l/lib.h"
 #include "../l/graph.h"

class exkurzia {
public:
    int off;
    TwoSat *S;

    void add(int l, int r, int i, int ig, int f, bool w) {
        if (l == ig && r == ig + 1) {
            return;
        } else if (ig >= r || ig < l) {
            S->addImplication(f, w, off + i, true);
        } else {
            add(l, (l+r)/2, 2*i, ig, f, w);
            add((l+r)/2, r, 2*i+1, ig, f, w);
        }

    };

void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int>> R(N);
    for (int i = 0; i < K; ++i) {
        int a, b; cin >> a >> b;
        R[a-1].push_back(b);
    }

    S = new TwoSat(M + 4*K);
    off = M;

    for (int i = 0; i < N; ++i) {
        int s = R[i].size();
        if (s == 0) continue;
        int h = 1<<logceil(s);
        for (int j = 1; j < h; ++j) {
            S->addImplication(off+j, true, off+2*j, true);
            S->addImplication(off+j, true, off+2*j+1, true);
        }
        for (int j = 0; j < s; ++j) {
            int t = abs(R[i][j])-1;
            bool d = R[i][j] > 0;
            S->addImplication(off+h+j, true, t, d);
            add(0, h, 1, j, t, !d);
        }

        off += 2*h;
    }

    if (S->solve()) {
        vector<int> P;
        for (int i = 0; i < M; ++i) if (S->val[2*i]<0) P.push_back(i+1);
        cout << P.size() << '\n' << P;
    } else {
        cout << "-1\n";
    }
}
};
