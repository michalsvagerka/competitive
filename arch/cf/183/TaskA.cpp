#include "../l/lib.h"
// #include "../l/mod.h"
#include <numeric>
class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    if (N%2 == 0) {
        cout << "-1\n";
        return;
    }
    
    vector<int> A(N);
    iota(A.begin(),A.end(),0);
    cout << A << A;
    for (int &a:A) a = (2*a)%N;
    cout << A;
}
};
