#include "../l/lib.h"

class APrefixSumPrimes {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int a = 0, b = 0;
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            if (x == 1) a++; else b++;
        }

        vector<int> Ans;
        if (b) {
            Ans.push_back(2);
            --b;
        }
        if (a) {
            Ans.push_back(1);
            --a;
        }

        while (b) {
            Ans.push_back(2);
            --b;
        }
        while (a) {
            Ans.push_back(1);
            --a;
        }
        cout << Ans;
    }
};
