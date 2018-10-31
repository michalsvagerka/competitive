#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N);
    cin >> A;
    for (int k = *max_element(A.begin(),A.end()); ; ++k) {
        int x = 0, y = 0;
        for (int &a:A) {
            x += a;
            y += k - a;
        }
        if (y > x) {
            cout << k << '\n';
            return;
        }
    }
}
};
