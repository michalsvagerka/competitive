#include "../l/lib.h"
#include "../l/mod.h"

class BReversi {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> C(N); cin >> C;
        vector<int> D{C[0]};
        for (int j = 1; j < N; ++j) {
            if (C[j] != D.back()) D.push_back(C[j]);
        }
        N = D.size();

        vector<FieldMod> Q(2e5+1, 0);
        Q[0] = 1;
        for (int i = 0; i < N; ++i) {
            int c = D[i];
            FieldMod q0 = Q[0];
            FieldMod qc = Q[c];
            Q[0] = Q[c] = q0+qc; 
        }
        cout << Q[0] << endl;
    }
};
