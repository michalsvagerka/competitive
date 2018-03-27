#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        vector<int> X(N);
        cin >> X;
        map<int, int> C;
        vector<bool> hasChange(N, false);
        vector<int> MX2(N);
        int mx2 = -1;
        for (int i = 0; i < N; ++i) {
            ++C[X[i]];
            if (C[X[i]] == 3) {
                cout << "-1\n";
                return;
            }

            if (C[X[i]] == 2) {
                if (X[i] < mx2) {
                    cout << "-1\n";
                    return;
                }

                if (C.rbegin()->x > X[i]) hasChange[i] = true; // _HI, LO, _LO

                mx2 = X[i];
            }

            MX2[i] = mx2;
        }
//        cout << hasChange;

        int mx = X[N - 1];
        int mn1 = -1, mn2 = -1;
        int b = N - 1;
        while (b > 0 && X[b - 1] > X[b]) {
            hasChange[b] = true;
            --b;
        }

        for (int i = N - 1; i >= 0; --i) {
            if (mn1 != -1 && X[i] >= mn1) {
                hasChange[i] = true; // _HI, LO, ME
            }

            if (X[i] < mn2) {
                mn1 = mn2;
                mn2 = X[i];
            }

            if (X[i] < mn1) mn1 = X[i];
            if (mn2 == -1) mn2 = X[i];
        }

        int lo = 0, hi = 1000000001;
        for (int i = 0; i < N; ++i) {
            if (hasChange[i]) {
                if (X[i] >= hi) {
                    cout << "-1\n";
                    return;
                }
                hi = X[i];
            } else {
                if (X[i] <= lo) {
                    cout << "-1\n";
                    return;
                }
                lo = X[i];
            }
        }


        int maxK = 1000000001, minK = 0;
        for (int i = 0; i < N - 1; ++i) {
            if (hasChange[i] && !hasChange[i + 1]) {
                maxK = min(maxK, X[i] + X[i + 1] - 1);
            } else if (!hasChange[i] && hasChange[i + 1]) {
                minK = max(minK, X[i] + X[i + 1] + 1);
            }

            if (hasChange[i]) {
                minK = max(minK, X[i]);
            }
        }

        if (minK > maxK) {
            cout << "-1\n";
            return;
        }

        vector<int> Z(N);

        for (int i = 0; i < N; ++i) {
            if (hasChange[i]) {
                Z[i] = minK - X[i];
            } else {
                Z[i] = X[i];
            }
        }

        for (int i = 0; i < N - 1; ++i) {
            if (Z[i] >= Z[i + 1]) {
                cout << "-1\n";
                return;
            }
        }

        cout << minK << endl << Z;
    }
};
