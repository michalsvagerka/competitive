#include "../../../l/lib.h"
#include "../../../l/segtree.h"
#include "../../../l/mod.h"

class req {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> D(1e6+1, 0);
        for (int i = 2; i <= 1e6; ++i) {
            if (!D[i]) {
                for (int j = i; j <= 1e6; j+=i) D[j] = i;
            }
        }

        int N; cin >> N;
        vector<FieldMod> A(N); cin >> A;

        map<int, vector<int>> Factors;
        map<int, int> UsedFactors;
        vector<vector<int>> FirstOccurrence(N);
        for (int i = 0; i < N; ++i) {
            int a = (ui)A[i];
            while (a != 1) {
                while (D[a/D[a]] == D[a]) a /= D[a];
                Factors[D[a]].push_back(i);
                UsedFactors[D[a]] = 0;
                a /= D[a];
            }
        }

        SetMulTree<FieldMod> Product, Kill;
        Product.setup(A, 1);
        Kill.setup(N, 1);

        for (auto&f:Factors) {
            FirstOccurrence[f.y[0]].push_back(f.x);
            Kill.put(f.y[0], Kill.get(f.y[0]) * FieldMod{f.x-1}/f.x);
        }


        int Q; cin >> Q;
        vector<vector<pii>> Queries(N);
        for (int i = 0; i < Q; ++i) {
            int l, r; cin >> l >> r;
            --l; --r;
            Queries[l].push_back({r,i});
        }

        vector<FieldMod> Ans(Q);
        for (int left = 0; left < N; ++left) {
            for (pii query : Queries[left]) {
                Ans[query.y] = Product.get(left, query.x) * Kill.get(left, query.x);
            }

            for (int prime: FirstOccurrence[left]) {
                if (++UsedFactors[prime] < Factors[prime].size()) {
                    int nextId = Factors[prime][UsedFactors[prime]];
                    Kill.put(nextId, Kill.get(nextId) * FieldMod{prime-1}/prime);
                    FirstOccurrence[nextId].push_back(prime);
                }
            }
        }

        for (auto ans:Ans) cout << ans << '\n';

    }
};
