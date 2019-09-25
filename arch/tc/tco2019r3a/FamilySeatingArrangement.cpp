#include "../l/lib.h"
#include "../l/mod.h"

class FamilySeatingArrangement {
public:
    int countWays(vector <int> a, int k) {
        int N = a.size();
        auto F = FieldMod::fact(2001);
        auto I = FieldMod::invfact(2001);
        vector<FieldMod> C(k+1, 0);
        for (int i = 1; i <= min(N, k); ++i) C[i] = FieldMod{i}.pow(N);
        for (int i = min(N, k); i >= 1; --i) {
            for (int j = 1; j < i; ++j) {
                FieldMod x = C[j] * F[i] * I[j] * I[i-j];
                if ((i-j)%2==0) C[i] += x; else C[i] -= x;
            }
        }
        for (int i = 1; i <= k; ++i) C[i] *= F[k] * I[i] * I[k-i];

        int tot = 0;
        for (int A:a) tot += A;
        FieldMod ans = 0;
        for (int i = 1; i <= k; ++i) {
            ans += C[i] * FieldMod{k-i+1}.pow(tot);
        }
        return (ui)ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << countWays({2,1},2) << endl;
        cout << countWays({2,1},3) << endl;
        cout << countWays({2,1,3},3) << endl;
        cout << countWays({2,1},1000) << endl;
        cout << countWays({1,1,1,1,1,1,1,1,1,1,1,1}, 8) << endl;
        cout << countWays({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},211) << endl;
        cout << countWays(vector<int>(1000, 1),1000) << endl;

    }
};
