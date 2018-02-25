#include "../../../l/lib.h"
#include "../../../l/matrix.h"
#include "../../../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(M); cin >> A;
        A.push_back(N);

        Matrix<FieldMod> C{{
                                   {1, 0, 0, 1},
                                   {2, 1, 0, 2},
                                   {1, 1, 1, 1},
                                   {1, 1, 1, 1}
                           }};

        vector<Matrix<FieldMod>> P{C};
        for (int i = 0; i < 30; ++i) P.push_back(P[i]*P[i]);

        vector<FieldMod> v{1,0,0,0};
        int cur = 0;
        for (int a:A) {
            for (int i = 0; i < 31; ++i) {
                if ((a-cur)&(1<<i)) v = P[i] * v;
            }

            if (a != N) v[3] = 0;
            cur = a;
        }

        cout << v[3] << endl;
    }
};
