#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    ll A, B; cin >> A >> B;
    ll K = 0;
    while ((K+2) * (K+1) / 2 <= A+B) ++K;
    vector<int> C, D;
    for (int k = K; k >= 1; --k) {
        if (A >= k) {
            C.push_back(k);
            A -= k;
        } else {
            D.push_back(k);
        }
    }
    
    cout << C.size() << endl << C << D.size() << endl << D;
}
};
