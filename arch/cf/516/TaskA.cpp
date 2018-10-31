#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    string S; cin >> S;
    sort(S.begin(),S.end());
    cout << S << endl;
}
};
