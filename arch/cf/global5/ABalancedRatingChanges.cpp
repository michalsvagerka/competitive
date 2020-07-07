#include "../../../l/lib.h"

class ABalancedRatingChanges {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;

        int sum = 0;
        vector<int> B(N);
        for (int i = 0; i < N; ++i) {
            if (A[i] < 0) B[i] = (A[i]-1)/2; else B[i] = A[i]/2;
            sum += B[i];
        }

        for (int i = 0; i < N; ++i) {
            if (A[i]%2!=0 && sum != 0) {
                B[i]++;
                sum++;
            }
        }
        
        for (int&b:B) cout <<b  << '\n';
    }
};
