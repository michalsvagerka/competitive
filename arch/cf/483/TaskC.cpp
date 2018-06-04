#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    map<vector<int>, int> M1;
    vector<vector<int>> M2;
    vector<int> W;

    void gen(int i, int j) {
        if (j == 9) {
            int z = M2.size();
            M1[W] = z;
            M2.push_back(W);
            return;
        }

        gen(i, j+1);
        for (int k = i+1; k <= 4; ++k) {
            W.push_back(j);
            gen(k, j+1);
        }
        for (int k = i+1; k <= 4; ++k) {
            W.pop_back();
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N); cin >> A;
        for (auto &a:A) { --a.x; --a.y; }

        gen(0, 0);

        int inf = 1e9;
        vector3<int> W(N+1, 9, M2.size(), inf);
        W[0][0][0] = 0;

        vector<pair<pii,int>> S{{{0,0},0}};
        for (int s = 0; s < S.size(); ++s) {
            int p = S[s].x.x;
            int f = S[s].x.y;
            int a = S[s].y;
            vector<int> T = M2[a];
            T.erase(remove(T.begin(), T.end(), f), T.end());
            if (p == N && T.empty()) {
                cout << W[p][f][a] + 2*N << '\n';
                return;
            }
            int r = p;
            while (r < N && A[r].x == f && T.size() < 4) { T.push_back(A[r].y); ++r; }
            sort(T.begin(),T.end());
            int b = M1[T];

            for (int df = -1; df <= 1; df+=2) {
                int g = f + df;
                if (g >= 0 && g < 9) {
                    if (W[r][g][b] == inf) {
                        W[r][g][b] = W[p][f][a] + 1;
                        S.push_back({{r,g},b});
                    }
                }
            }
        }
    }
};
