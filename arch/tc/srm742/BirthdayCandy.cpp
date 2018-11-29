#include "../l/lib.h"
// #include "../l/mod.h"

class BirthdayCandy {
public:
    int mostCandy(int K, vector <int> candy) {
        int ans = 0;
        ++K;
        for (int c: candy) ans = max(ans, c/K + c%K);
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << mostCandy(9, {23, 7}) << endl;
        cout << mostCandy(1, {1, 2}) << endl;
        cout << mostCandy(4, {43, 81, 17, 1, 9}) << endl;
        cout << mostCandy(6, {7}) << endl;
    }
};
