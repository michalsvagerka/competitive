#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    pii ans = {N+1, 1};
    for (int i = 2; i <= N; ++i) {
        int lis = i;
        int lds = (N+lis-1)/lis;
        ans = min(ans, {lis+lds, i});
    }

    vector<int> Ans;
    int lis = ans.y;
    int lds = (N+lis-1)/lis;
    for (int i = lds-1; i >= 0; --i) {
        for (int j = i*lis; j < min((i+1)*lis, N); ++j) {
            Ans.push_back(j+1);
        }
    }
    cout << Ans;
}
};
