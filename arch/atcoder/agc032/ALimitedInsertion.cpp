#include "../l/lib.h"

class ALimitedInsertion {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> Sol;
        while (N) {
            bool found = false;
            for (int j = N-1; j >= 0; --j) {
                if (A[j] == j+1) {
                    Sol.push_back(j+1);
                    for (int k = j; k < N-1; ++k) {
                        A[k] = A[k+1];
                    }
                    A.pop_back();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "-1\n";
                return;
            }
            
            --N;
        }
        
        reverse(Sol.begin(),Sol.end());
        for (int s: Sol) cout << s << '\n';
    }
};
