#include "../l/lib.h"
// #include "../l/mod.h"

class DMedianPyramidHard {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(2*N-1); cin >> A;
    cout << bsh(1, 2*N-1, [&](int t) {
        vector<int> W(2*N-1);
        for (int i = 0; i < 2*N-1; ++i) W[i] = A[i] >= t;
        int j = N-1;
        while (j < 2*N-2 && W[j] != W[j+1]) ++j;
        int k = N-1;
        while (k > 0 && W[k] != W[k-1]) --k;
        return 2*N-2 < j+k ? W[k] : W[j];
    }) << endl;
}
};
