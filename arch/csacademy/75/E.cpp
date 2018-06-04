#include "../../../l/lib.h"
#include "../../../l/consttree.h"
#include "../../../l/segtree.h"

constexpr int M = 40000;

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> A(N); cin >> A;
        vector<int> Ans(Q, -1);
        vector<vector<pair<int, pii>>> R(M+1);
        for (int i = 0; i < Q; ++i) {
            int l, r, k; cin >> l >> r >> k;
            --l; --r;
            R[k].push_back({i, {l,r}});
        }

        int lo = 100;
        for (int i = 1; i <= lo; ++i) {
            vector<int> B(N);
            for (int j = 0; j < N; ++j) B[j] = A[j] % i;
            ConstTree<int, MaxQOp<int>> CT(B);
            for (auto &q: R[i]) {
                int l = q.y.x;
                int r = q.y.y;
                Ans[q.x] = max(Ans[q.x], CT.get(l,r));
            }
        }

        vector<vector<int>> OC(M+1);
        for (int i = 0; i < N; ++i) OC[A[i]].push_back(i);
        vector<vector<int>> CHK(M+1);
        for (int i = lo+1; i <= M; ++i) {
            for (int j = i-1; j <= M; j+=i) {
                CHK[j].push_back(i);
            }
            CHK[M].push_back(i);
        }


        SetMaxTree<int> S;
        S.setup(N, 0);
        for (int i = 1; i <= M; ++i) {
            for (int s:OC[i]) {
                S.put(s, i);
            }
//
//            if (i < 10) {
//                for (int i = 0; i < N; ++i) {
//                    cout << S.get(i) << ' ';
//                }
//                cout << endl;
//            }


            for (int chk:CHK[i]) {
                //if (i < 20) cout << "Chk " << i << ' ' << chk << endl;
                for (auto &q: R[chk]) {
                    //if (i < 20) cout << "Chk " << i << ' ' << q << endl;
                    int l = q.y.x;
                    int r = q.y.y;
                    Ans[q.x] = max(Ans[q.x], S.get(l,r)%chk);
                }
            }
        }


        for (int a:Ans) cout << a << '\n';
    }
};
