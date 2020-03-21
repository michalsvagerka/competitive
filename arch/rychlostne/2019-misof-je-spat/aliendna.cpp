#include "../l/lib.h"
#include "../l/mod.h"

class aliendna {
public:
    void solve(istream& cin, ostream& cout) {
        int G, N;
        cin >> G >> N;
        vector<int> A(N);
        cin >> A;
        if (G > N) {
            set<int> Have;
            for (int a: A) Have.insert(a);
            cout << 1 << '\n' << G - Have.size() << '\n';
            return;
        }

        vector<vector<int>> R(G);
        for (int i = 0; i < N; ++i) R[A[i]].push_back(i);
        int empty = 0;
        for (int i = 0; i < G; ++i) empty += R[i].empty();
        if (empty) {
            cout << 1 << '\n' << empty << endl;
            return;
        }

        vector<FieldMod> D(N, 0);
        int lo = N;
        for (int g = 0; g < G; ++g) {
            int f = R[g].back();
            D[N-1]++;
            if (f != 0) D[f-1]--;
            lo = min(lo, f);
        }

        for (int j = N-1; j >= lo; --j) {
            if (j != 0) D[j - 1] += D[j];
        }

        FieldMod ans = 0;
        int hi = N-1;
        for (int l = 1; l <= N; ++l) {
            int newLo = N;
            for (int i = hi; i >= lo; --i) {
                int g = A[i];
                R[g].pop_back();
                if (R[g].empty()) {
                    ans += D[i];
                    newLo = -1;
                } else {
                    int f = R[g].back();
                    if (f < lo+1) {
                        if (f!=0) D[f-1] -= D[i];
                        D[lo-1] += D[i];
                    }
                    newLo = min(newLo, f);
                }
            }

            if (newLo == -1) {
                cout << l + 1 << '\n' << ans << endl;
                return;
            }

            for (int j = lo-1; j >= newLo; --j) {
                if (j != 0) D[j - 1] += D[j];
            }

            hi = lo-1;
            lo = newLo;
        }
    }
};
