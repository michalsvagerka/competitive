#include "../../../l/lib.h"
#include "../../../l/consttree.h"
#include "../../../l/mod.h"

class rovnakemax {
public:
    FieldMod cmb(int len) {
        return FieldMod{len} * FieldMod{len-1} / 2 + len;
    }

    FieldMod pairs(int len) {
        return
                FieldMod{len} * FieldMod{len-1} * FieldMod{len-2} * FieldMod{len-3} / 24
                + FieldMod{len} * FieldMod{len-1} * FieldMod{len-2} / 3
                + FieldMod{len} * FieldMod{len-1} / 2;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        ConstTree<int, MaxQOp<int>> H(A);
        unordered_map<int, map<pii, vector<int>>> S;
        for (int i = 0; i < N; ++i) {
            int l = bsl(0, i, [&](int j) { return H.get(j,i) == A[i]; });
            int r = bsh(i, N-1, [&](int j) { return H.get(i,j) == A[i]; });
            S[A[i]][{l,r}].push_back(i);
        }

        FieldMod ans = 0;
        for (auto &s: S) {
            FieldMod dbl = 0;
            FieldMod sumx = 0;
            FieldMod sumx2 = 0;


            vector<FieldMod> Z(5, 0);
            Z[0] = 1;
            for (auto &t: s.y) {
                int prev = t.x.x;
                for (int G : t.y) {
                    vector<FieldMod> Q = Z;
                    int l = G-prev;
                    for (int i = 0; i < 4; ++i) Q[i+1] += Z[i] * (l+1);
                    Q[3] += Z[1] * (l+1) * l / 2;
                    Q[2] += Z[0] * (l+1);
                    Q[4] += Z[2] * (l+1);
                    Q[4] += Z[1] * (l+1) * l / 2;
                    prev = G+1;
                    swap(Q,Z);
//                    cerr << s.x << ' ' << l << ' ' << Z;
                }
                int l = t.x.y - prev + 1;

                vector<FieldMod> Q = Z;
                for (int i = 0; i < 4; ++i) Q[i+1] += Z[i] * l;
                swap(Q,Z);
                Z[1] = Z[3] = 0;

//                cerr << s.x << ' ' << l <<  ' ' << Z;
            }

            ans += Z[4];
        }
        cout << ans << endl;
    }
};
