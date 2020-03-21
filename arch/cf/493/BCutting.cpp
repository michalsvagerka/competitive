#include "../l/lib.h"

class BCutting {
public:
    void solve(istream& cin, ostream& cout) {
        int N, B; cin >> N >> B;
        vector<int> A(N); cin >> A;
        int b = 0;
        vector<int> C;
        for (int i = 0; i < N-1; ++i) {
            if (A[i]%2==0) b++; else b--;
            if (b==0) C.push_back(abs(A[i+1]-A[i]));
        }
        sort(C.begin(),C.end());
        int ans = 0;
        while (ans < C.size() && B >= C[ans]) B -= C[ans++];
        cout << ans << '\n';
    }
};
