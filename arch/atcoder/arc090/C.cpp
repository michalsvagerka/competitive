#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N);
        vector<int> B(N);
        cin >> A >> B;
        for (int i = 1; i < N; ++i) {
            A[i] += A[i-1];
            B[N-i-1] += B[N-i];
        }

        for (int i = 0; i < N; ++i) {
            A[i] += B[i];
        }

        cout << *max_element(A.begin(),A.end()) << endl;
    }
};
