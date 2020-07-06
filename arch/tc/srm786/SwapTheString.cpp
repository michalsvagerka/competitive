#include "../l/lib.h"

class SwapTheString {
public:
    long long findNumberOfSwaps(string P, int A0, int X, int Y, int N, int K) {
        vector<ll> A(N);
        A[0] = A0;
        for (int i = 1; i < N; ++i)
            A[i] = (A[i-1] * X + Y) % 1812447359;

        string S = P;
        for (int i = P.size(); i < N; ++i)
            S += (char)(A[i] % 26 + 'a');

        ll ans = 0;
        for (int i = 0; i < K; ++i) {
            vector<int> C(26, 0);
            for (int j = i; j < N; j += K) {
                int g = S[j]-'a';
                for (int k = 0; k < g; ++k) ans += C[k];
                C[g]++;
            }

        }
        return ans;
    }
    void solve(istream& cin, ostream& cout) {
        cout << findNumberOfSwaps("cbexa",0,0,0,5,2) << '\n';
        cout << findNumberOfSwaps("",5,2,3,4,1) << '\n';
        cout << findNumberOfSwaps("b",1001,1001,1001,5,2) << '\n';
        cout << findNumberOfSwaps("",9999,50000,4797,6,3) << '\n';
        cout << findNumberOfSwaps("",3435,1000000000,1812447358,7,2) << '\n';
    }
};
