#include "../l/lib.h"
#include "../l/util.h"

class DWojtekAndCardTricks {
public:
    vector<int> apply(const vector<int>&A, const vector<int>&B) {
        vector<int> C(A.size());
        for (int i = 0; i < A.size(); ++i) C[i] = A[B[i]];
        return C;
    }

    void solve(istream& cin, ostream& cout) {
        int N, K;
        cin >> N >> K;
        vector2<int> P(N, K);

        cin >> P;
        for (auto &p:P) for (auto &pp:p) --pp;

        map<vector<int>, int> Q;
        vector<vector<int>> PRM;
        vector<int> I(K);
        int c = 0;
        iota(I.begin(),I.end(),0);
        do {
            PRM.push_back(I);
            Q[I] = c++;
        } while (next_permutation(I.begin(),I.end()));

        vector2<int> APP(c, c);
        for (int i = 0; i < c; ++i) {
            for (int j = 0; j < c; ++j) {
                APP[i][j] = Q[apply(PRM[i], PRM[j])];
            }
        }

        vector<int> RealIn(N);
        for (int i = 0; i < N; ++i) RealIn[i] = Q[P[i]];

        ll ans = 0;
        vector<int> Next(c, N);
        for (int i = N-1; i >= 0; --i) {
            Next[RealIn[i]] = i;
            vector<int> Add;
            for (int j = 0; j < c; ++j) if (Next[j] != N) Add.push_back(Next[j]);
            sort(Add.begin(),Add.end());
            UnionFind UF(c);
            int prev = i;
            for (int a: Add) {
                int sz = UF.size(0);
                if (sz == c) break;

                ans += (a-prev)*sz;
                int v = RealIn[a];
                if (!UF.united(0, v)) for (int i = 0; i < c; ++i) UF.unite(i, APP[v][i]);
                prev = a;
            }

            ans += (N-prev) * UF.size(0);
        }

        cout << ans << endl;
    }
};
