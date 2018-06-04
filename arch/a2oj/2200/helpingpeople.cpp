#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/consttree.h"

class helpingpeople {
public:

    vector<pair<pii,double>> R;
    int N, Q;

    void combine(vector<double>&Z, const vector<double>&W) {
        double totZ = 0, totW = 0;
        for (int i = 2*Q; i >= 0; --i) {
            totZ += Z[i];
            totW += W[i];

            Z[i] = Z[i] * (1-totW) + W[i] * (1-totZ) + Z[i] * W[i];
        }
    }

    void setMin(vector<double>&Z, int q) {
        double tot = 0;
        for (int i = 0; i <= q; ++i) { tot += Z[i]; Z[i] = 0; }
        Z[q] = tot;
    }

    void add(vector<double>&Z, double p) {
        for (int i = 2*Q; i > 0; --i) {
            Z[i] += Z[i-1]*p;
            Z[i-1] *= (1-p);
        }
    }

    void solve(int & j, ConstTree<int, MaxQOp<int>> &T, vector<double> &Z) {
        auto &r = R[j];
        j++;
        int left = r.x.x;
        while (j < R.size() && R[j].x.x <= r.x.y) {
            if (left != R[j].x.x) {
                int hi = T.get(left, R[j].x.x-1);
                setMin(Z, hi);
            }

            left = R[j].x.y+1;
            vector<double> W(2*Q+1, 0);
            W[0] = 1;
            solve(j, T, W);
            combine(Z, W);
        }

        if (left <= r.x.y) {
            int hi = T.get(left, r.x.y);
            setMin(Z, hi);
        }

        add(Z, r.y);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> Q;
        vector<int> A(N); cin >> A;
        int of = *max_element(A.begin(),A.end())-Q;
        for (int&a:A) a = max(0, a-of);

        ConstTree<int, MaxQOp<int>> T{A};
        R.resize(Q); cin >> R;
        for (auto&r:R) { --r.x.x; --r.x.y; }
        R.push_back({{0,N-1}, 0});
        sort(R.begin(),R.end(),[](const pair<pii,double>&a, const pair<pii,double>&b) { return a.x.x < b.x.x || (a.x.x == b.x.x && a.x.y > b.x.y); });

        int j = 0;
        vector<double> Z(2*Q+1, 0);
        Z[0] = 1;
        solve(j, T, Z);
        double ans = of;
        for (int i = Q; i <= 2*Q; ++i) {
            ans += Z[i]*i;
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
};
