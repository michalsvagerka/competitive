#include "../l/lib.h"

class DReplaceByMEX {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            vector<int> B;
            int i = 0;
            while (i < N) {
                if (A[i] == i) {
                    ++i;
                    continue;
                }

                set<int> MX;
                for (int j = 0; j < N; ++j) MX.insert(A[j]);
                int k = 0;
                while (MX.count(k)) ++k;

                if (k < N) {
                    A[k] = k;
                    B.push_back(k+1);
                    if (i == k) i++;
                } else {
                    for (int j = 0; j < N; ++j) {
                        if (A[j] == i) {
                            A[j] = k;
                            B.push_back(j+1);
                            break;
                        }
                    }
                }
            }


            cout << B.size() << '\n' << B;
        }
    }
};
